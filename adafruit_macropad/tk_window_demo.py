#!/usr/bin/env python3
"""Tkinter window with USB/serial port: connect, send text, and read incoming text."""

import random
import tkinter as tk
from tkinter import ttk, scrolledtext, messagebox
import queue
from datetime import datetime

try:
    import serial
    import serial.tools.list_ports
except ImportError:
    serial = None


def list_serial_ports():
    """Return list of (port, description) for combo."""
    if serial is None:
        return []
    ports = serial.tools.list_ports.comports()
    return [(p.device, f"{p.device} — {p.description}") for p in ports]


class SerialWindow:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("USB Serial — Read & Send Text")
        self.root.geometry("720x420")
        self.root.resizable(True, True)

        self.ser = None
        self.read_queue = queue.Queue()
        self.reading = False
        self._after_id = None
        self.current_turn = None  # "rtrn" or "btrn" when game mode active
        self.board = [None] * 9   # None or "red" or "blue" per cell 0..8
        self._read_buffer = ""   # incomplete serial input until newline

        self._build_ui()

    def _build_ui(self):
        # Top: port and baud
        top = ttk.Frame(self.root, padding=4)
        top.pack(fill=tk.X)

        ttk.Label(top, text="Port:").pack(side=tk.LEFT, padx=(0, 4))
        self.port_var = tk.StringVar()
        self.port_combo = ttk.Combobox(
            top, textvariable=self.port_var, width=24, state="normal"
        )
        self.port_combo.pack(side=tk.LEFT, padx=(0, 8))
        if serial:
            ports = list_serial_ports()
            if ports:
                self.port_combo["values"] = [p[0] for p in ports]
                self.port_combo.set(ports[0][0])
            else:
                self.port_combo.set("/dev/ttyUSB0" if __import__("sys").platform != "win32" else "COM1")

        ttk.Label(top, text="Baud:").pack(side=tk.LEFT, padx=(12, 4))
        self.baud_var = tk.StringVar(value="115200")
        baud_combo = ttk.Combobox(
            top, textvariable=self.baud_var, width=8, state="readonly"
        )
        baud_combo["values"] = ("9600", "19200", "38400", "57600", "115200", "230400")
        baud_combo.pack(side=tk.LEFT, padx=(0, 8))

        self.connect_btn = ttk.Button(top, text="Connect", command=self._toggle_connect)
        self.connect_btn.pack(side=tk.LEFT, padx=(12, 0))

        # Red / Blue command buttons (position selection; disabled in game mode — use macropad only)
        btn_frame = ttk.LabelFrame(self.root, text="Commands", padding=4)
        btn_frame.pack(fill=tk.X, padx=6, pady=4)
        red_frame = ttk.Frame(btn_frame)
        red_frame.pack(fill=tk.X)
        ttk.Label(red_frame, text="Red:").grid(row=0, column=0, padx=(0, 6), sticky=tk.W)
        self.red_buttons = []
        for i in range(9):
            cmd = f"sr0{i}"
            b = ttk.Button(red_frame, text=f"red_{i}", command=lambda c=cmd: self._send_command(c))
            b.grid(row=0, column=i + 1, padx=2)
            self.red_buttons.append(b)
        blue_frame = ttk.Frame(btn_frame)
        blue_frame.pack(fill=tk.X, pady=(4, 0))
        ttk.Label(blue_frame, text="Blue:").grid(row=0, column=0, padx=(0, 6), sticky=tk.W)
        self.blue_buttons = []
        for i in range(9):
            cmd = f"sb0{i}"
            b = ttk.Button(blue_frame, text=f"blue_{i}", command=lambda c=cmd: self._send_command(c))
            b.grid(row=0, column=i + 1, padx=2)
            self.blue_buttons.append(b)
        turn_frame = ttk.Frame(btn_frame)
        turn_frame.pack(fill=tk.X, pady=(8, 0))
        ttk.Label(turn_frame, text="Turn:").pack(side=tk.LEFT, padx=(0, 8))
        ttk.Button(turn_frame, text="Red's turn", command=lambda: self._send_command("rtrn")).pack(
            side=tk.LEFT, padx=4
        )
        ttk.Button(turn_frame, text="Blue's turn", command=lambda: self._send_command("btrn")).pack(
            side=tk.LEFT, padx=4
        )
        ttk.Button(turn_frame, text="Clear board", command=self._on_clear_board).pack(
            side=tk.LEFT, padx=4
        )
        ttk.Button(turn_frame, text="Game mode", command=self._on_game_mode).pack(
            side=tk.LEFT, padx=4
        )

        # Log (received + sent, with timestamps)
        ttk.Label(self.root, text="Log (recv / sent):").pack(anchor=tk.W, padx=6, pady=(8, 0))
        self.recv_text = scrolledtext.ScrolledText(
            self.root, height=10, font=("Consolas", 10), state=tk.DISABLED
        )
        self.recv_text.pack(fill=tk.BOTH, expand=True, padx=6, pady=4)

        # Send
        send_frame = ttk.Frame(self.root, padding=4)
        send_frame.pack(fill=tk.X)
        ttk.Label(send_frame, text="Send:").pack(side=tk.LEFT, padx=(0, 4))
        self.send_var = tk.StringVar()
        self.send_entry = ttk.Entry(send_frame, textvariable=self.send_var, width=40)
        self.send_entry.pack(side=tk.LEFT, fill=tk.X, expand=True, padx=4)
        self.send_entry.bind("<Return>", lambda e: self._send())
        ttk.Button(send_frame, text="Send", command=self._send).pack(side=tk.LEFT)

    def _toggle_connect(self):
        if self.ser is not None and self.ser.is_open:
            self._disconnect()
        else:
            self._connect()

    def _connect(self):
        if serial is None:
            messagebox.showerror("Error", "Install pyserial: pip install pyserial")
            return
        port = self.port_var.get().strip()
        if not port:
            messagebox.showwarning("Warning", "Enter a port (e.g. /dev/ttyUSB0 or COM3)")
            return
        try:
            baud = int(self.baud_var.get())
        except ValueError:
            baud = 9600
        try:
            self.ser = serial.Serial(port=port, baudrate=baud, timeout=0.1)
            self.reading = True
            self.connect_btn.config(text="Disconnect")
            self.port_combo.config(state=tk.DISABLED)
            self._poll_serial()
        except Exception as e:
            messagebox.showerror("Connection error", str(e))

    def _disconnect(self):
        self.reading = False
        self._read_buffer = ""
        if self._after_id:
            self.root.after_cancel(self._after_id)
            self._after_id = None
        if self.ser is not None:
            try:
                self.ser.close()
            except Exception:
                pass
            self.ser = None
        self.connect_btn.config(text="Connect")
        self.port_combo.config(state="normal")

    def _poll_serial(self):
        if not self.reading or self.ser is None or not self.ser.is_open:
            return
        try:
            data = self.ser.read(self.ser.in_waiting or 1)  
            if data:
                try:
                    text = data.decode("utf-8", errors="replace")
                except Exception:
                    text = data.hex()
                self.read_queue.put(text)
        except Exception:
            pass
        self._after_id = self.root.after(50, self._poll_serial)

    def _timestamp(self):
        return datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]

    def _append_log(self, prefix, text):
        """Append a timestamped line with prefix (sent: or recv:) to the log."""
        line = f"[{self._timestamp()}] {prefix} {text}\n"
        self.recv_text.config(state=tk.NORMAL)
        self.recv_text.insert(tk.END, line)
        self.recv_text.see(tk.END)
        self.recv_text.config(state=tk.DISABLED)

    def _drain_queue(self):
        while True:
            try:
                text = self.read_queue.get_nowait()
                self._read_buffer += text
            except queue.Empty:
                break
        # Split by newline: each complete line (followed by \n or \r) is one command
        parts = self._read_buffer.replace("\r", "\n").split("\n")
        self._read_buffer = parts.pop()  # last segment may be incomplete, keep in buffer
        for raw_line in parts:
            line = raw_line.strip()
            if line:
                self._append_log("recv:", line)
                self._handle_received(line)
        # If buffer is exactly a known token (device sent without newline), process and clear
        token = self._read_buffer.strip()
        if token in self._KEY_TO_CELL:
            self._append_log("recv:", token)
            self._handle_received(token)
            self._read_buffer = ""
        self.root.after(100, self._drain_queue)

    # Macropad sends kp03..kp11 for grid keys (key index 3–11 → cell 0–8). Also accept key_pressed_N.
    _KEY_TO_CELL = {f"kp{i:02d}": i - 3 for i in range(3, 12)}
    _KEY_TO_CELL.update({f"key_pressed_{i}": i - 3 for i in range(3, 12)})

    def _handle_received(self, text):
        """In game mode: on kp03..kp11 from macropad, set that cell to turn color and send srNN/sbNN."""
        if self.current_turn not in ("rtrn", "btrn") or self.ser is None or not self.ser.is_open:
            return
        color = "red" if self.current_turn == "rtrn" else "blue"
        for token in text.split():
            token = token.strip()
            cell = self._KEY_TO_CELL.get(token)
            if cell is not None and self.board[cell] is None:
                # Tell macropad to set this button's color to current turn (srNN = red, sbNN = blue)
                set_color_cmd = ("sr" if color == "red" else "sb") + f"{cell:02d}"
                self._send_command(set_color_cmd)
                self.board[cell] = color
                self.current_turn = "btrn" if color == "red" else "rtrn"
                self._send_command(self.current_turn)

    def _update_game_mode_ui(self):
        """In game mode only macropad selects position; disable Red/Blue position buttons."""
        state = "disabled" if self.current_turn is not None else "normal"
        for b in self.red_buttons + self.blue_buttons:
            b.config(state=state)

    def _on_clear_board(self):
        """Send clrb; exit game mode and re-enable position buttons."""
        if self.ser is not None and self.ser.is_open:
            self._send_command("clrb")
        self.current_turn = None
        self.board = [None] * 9
        self._update_game_mode_ui()

    def _on_game_mode(self):
        """Clear board, pick random first turn; position selection is macropad only."""
        if self.ser is None or not self.ser.is_open:
            messagebox.showinfo("Info", "Connect to a port first.")
            return
        self.board = [None] * 9
        self._send_command("clrb")
        self.current_turn = random.choice(["rtrn", "btrn"])
        self._send_command(self.current_turn)
        self._update_game_mode_ui()

    def _send_command(self, cmd):
        """Send a command over serial. Macropad expects exactly 4 bytes (no newline)."""
        if self.ser is None or not self.ser.is_open:
            messagebox.showinfo("Info", "Connect to a port first.")
            return
        try:
            self.ser.write(cmd.encode("utf-8")+b"\n")
            self._append_log("sent:", cmd)
        except Exception as e:
            messagebox.showerror("Send error", str(e))

    def _send(self):
        if self.ser is None or not self.ser.is_open:
            messagebox.showinfo("Info", "Connect to a port first.")
            return
        msg = self.send_var.get()
        if not msg:
            return
        try:
            self.ser.write(msg.encode("utf-8"))
            self._append_log("sent:", msg)
            self.send_var.set("")
        except Exception as e:
            messagebox.showerror("Send error", str(e))

    def run(self):
        self._drain_queue()
        self.root.protocol("WM_DELETE_WINDOW", self._on_close)
        self.root.mainloop()

    def _on_close(self):
        self._disconnect()
        self.root.destroy()


def main():
    app = SerialWindow()
    app.run()


if __name__ == "__main__":
    main()
