#!/usr/bin/env python3
"""Tkinter window with USB/serial port: connect, send text, and read incoming text."""

import tkinter as tk
from tkinter import ttk, scrolledtext, messagebox
import threading
import queue

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
        self.root.geometry("520x380")
        self.root.resizable(True, True)

        self.ser = None
        self.read_queue = queue.Queue()
        self.reading = False
        self._after_id = None

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
        self.baud_var = tk.StringVar(value="9600")
        baud_combo = ttk.Combobox(
            top, textvariable=self.baud_var, width=8, state="readonly"
        )
        baud_combo["values"] = ("9600", "19200", "38400", "57600", "115200", "230400")
        baud_combo.pack(side=tk.LEFT, padx=(0, 8))

        self.connect_btn = ttk.Button(top, text="Connect", command=self._toggle_connect)
        self.connect_btn.pack(side=tk.LEFT, padx=(12, 0))

        # Received text
        ttk.Label(self.root, text="Received:").pack(anchor=tk.W, padx=6, pady=(8, 0))
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

    def _drain_queue(self):
        while True:
            try:
                text = self.read_queue.get_nowait()
                self.recv_text.config(state=tk.NORMAL)
                self.recv_text.insert(tk.END, text)
                self.recv_text.see(tk.END)
                self.recv_text.config(state=tk.DISABLED)
            except queue.Empty:
                break
        self.root.after(100, self._drain_queue)

    def _send(self):
        if self.ser is None or not self.ser.is_open:
            messagebox.showinfo("Info", "Connect to a port first.")
            return
        msg = self.send_var.get()
        if not msg:
            return
        try:
            self.ser.write(msg.encode("utf-8"))
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
