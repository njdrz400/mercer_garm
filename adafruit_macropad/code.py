import time
import board
import terminalio
from adafruit_display_text import label
from adafruit_macropad import MacroPad

import usb_cdc

console = usb_cdc.data

text = "Mercer GARM Ready"

text_area = label.Label(terminalio.FONT, text=text)
text_area.x = 0
text_area.y = 10
board.DISPLAY.root_group = text_area

macropad = MacroPad()

# Initial write to console
console.write(text.encode("utf-8"))
# Track encoder switch state for edge detection
last_encoder_switch = macropad.encoder_switch_debounced.pressed


def blink_all(color, times=10, interval=0.3):
    """Blink all MacroPad pixels in `color` `times` times with `interval` seconds."""
    try:
        for _ in range(times):
            for i in range(len(macropad.pixels)):
                macropad.pixels[i] = color
            macropad.pixels.show()
            time.sleep(interval)
            macropad.pixels.fill(0)
            macropad.pixels.show()
            time.sleep(interval)
    except Exception as e:
        try:
            console.write(("blink error: " + str(e) + "\n").encode("utf-8"))
        except Exception:
            pass


def handle_serial():
    """Read available bytes from `console` and act on commands.

    When the ASCII command 'red_turn' is received (newline optional),
    set the top three MacroPad buttons (pixels 0-2) to red.
    """
    try:
        # Non-blocking check for available bytes
        if hasattr(console, "in_waiting"):
            n = console.in_waiting
            if not n:
                return
            data = console.read(n)
        else:
            # No in_waiting attribute: skip to avoid blocking
            return

        if not data:
            return

        try:
            text = data.decode("utf-8").strip()
        except Exception:
            text = str(data).strip()

        if text == "red_turn":
            for i in range(3):
                macropad.pixels[i] = (255, 0, 0)
            macropad.pixels.show()
        if text == "blue_turn":
            for i in range(3):
                macropad.pixels[i] = (0, 0, 255)
            macropad.pixels.show()
        if text == "clear_board":
            # Set keys 3 through 11 (pixels 3..11) to white
            for i in range(3, 12):
                macropad.pixels[i] = (255, 255, 255)
            macropad.pixels.show()
        # Commands of form R_<n> set the corresponding button (3 + n) red
        # e.g. R_0 -> pixel 3 (key 3), R_8 -> pixel 11 (key 11)
        if text.startswith("set_red_"):
            try:
                idx = int(text[7:])
                pixel = 3 + idx
                if 3 <= pixel <= 11:
                    macropad.pixels[pixel] = (255, 0, 0)
                    macropad.pixels.show()
                else:
                    try:
                        console.write(("R_ index out of range: " + str(idx) + "\n").encode("utf-8"))
                    except Exception:
                        pass
            except Exception as e:
                try:
                    console.write(("R_ parse error: " + str(e) + "\n").encode("utf-8"))
                except Exception:
                    pass
        if text.startswith("set_blue_"):
            try:
                idx = int(text[8:])
                pixel = 3 + idx
                if 3 <= pixel <= 11:
                    macropad.pixels[pixel] = (0, 0, 255)
                    macropad.pixels.show()
                else:
                    try:
                        console.write(("B_ index out of range: " + str(idx) + "\n").encode("utf-8"))
                    except Exception:
                        pass
            except Exception as e:
                try:
                    console.write(("B_ parse error: " + str(e) + "\n").encode("utf-8"))
                except Exception:
                    pass
        if text.startswith("set_white_"):
            try:
                idx = int(text[9:])
                pixel = 3 + idx
                if 3 <= pixel <= 11:
                    macropad.pixels[pixel] = (255, 255, 255)
                    macropad.pixels.show()
                else:
                    try:
                        console.write(("W_ index out of range: " + str(idx) + "\n").encode("utf-8"))
                    except Exception:
                        pass
            except Exception as e:
                try:
                    console.write(("W_ parse error: " + str(e) + "\n").encode("utf-8"))
                except Exception:
                    pass
        if text == "blue_blink":
            # Blink all blue
            blink_all((0, 0, 255))
        if text == "red_blink":
            # Blink all red
            blink_all((255, 0, 0))
    except Exception as e:
        try:
            console.write(("serial handler error: " + str(e) + "\n").encode("utf-8"))
        except Exception:
            pass

while True:
    event = macropad.keys.events.get()
    # Poll serial each loop to respond to external commands
    handle_serial()

    # Handle encoder switch presses (debounced)
    try:
        macropad.encoder_switch_debounced.update()
        encoder_pressed = macropad.encoder_switch_debounced.pressed
        if encoder_pressed and not last_encoder_switch:
            # rising edge: encoder was pressed
            try:
                console.write(("encoder_pressed\n").encode("utf-8"))
            except Exception:
                pass
        last_encoder_switch = encoder_pressed
    except Exception:
        # If debounced helper isn't available, try simple attribute
        try:
            enc = getattr(macropad, 'encoder_switch', False)
            if enc:
                try:
                    console.write(("encoder_pressed\n").encode("utf-8"))
                except Exception:
                    pass
        except Exception:
            pass

    def get_pressed_key(ev):
        """Return the 0-based key index if `ev` is a press, otherwise None."""
        if ev and ev.pressed:
            return ev.key_number
        return None

    key_index = get_pressed_key(event)
    if key_index is not None:
        # Write the key index to the console (as number)
        try:
            console.write(("key_pressed_" + str(key_index) + "\n").encode("utf-8"))
        except Exception:
            pass

    time.sleep(0.01)

