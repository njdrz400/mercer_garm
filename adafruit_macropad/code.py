import time
import board
import terminalio
from adafruit_display_text import label
from adafruit_macropad import MacroPad

import usb_cdc

console = usb_cdc.console
serial = usb_cdc.data

text = "Mercer GARM Ready"

text_area = label.Label(terminalio.FONT, text=text)
text_area.x = 0
text_area.y = 10
board.DISPLAY.root_group = text_area

macropad = MacroPad()

# Initial write to console
#console.write(text.encode("utf-8"))
# Track encoder switch state for edge detection
last_encoder_switch = macropad.encoder_switch_debounced.pressed

# Buffer for incomplete 4-byte commands (bytes can arrive merged)
serial_cmd_buf = bytearray()


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



def execute_command(text):
      
    if text == "rtrn":
        # red turn: set keys 0-2 (pixels 0-2) to red
        for i in range(3):
            macropad.pixels[i] = (32, 0, 0)
        macropad.pixels.show()
    if text == "btrn":
        # blue turn: set keys 0-2 (pixels 0-2) to blue
        for i in range(3):
            macropad.pixels[i] = (0, 0, 32)
        macropad.pixels.show()
    if text == "clrb":
        # Set keys 3 through 11 (pixels 3..11) to white
        for i in range(3, 12):
            macropad.pixels[i] = (1, 1, 1)
        macropad.pixels.show()
    # Commands of form srNN / sbNN / swNN (4 bytes): set pixel 3+NN
    if text[0:2] == "sr":
        try:
            idx = int(text[2:4])
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
    if text[0:2] == "sb":
        try:
            idx = int(text[2:4])
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
    if text[0:2] == "sw":
        try:
            idx = int(text[2:4])
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
    if text == "bwin":
        blink_all((0, 0, 255))
    if text == "rwin":
        blink_all((255, 0, 0))
#------------------------------------------------------------------------------  
# Serial handling loop: continuously read from serial and execute commands    
#------------------------------------------------------------------------------
def handle_line(line):
    line = line.strip()
    if not line:
        return
    execute_command(line)

def handle_key_event(event):
    # Send key events to console as "kX\n" where X is 0-11

    try:
        if event.key_number <= 9:
            serial.write(("kp0" + str(event.key_number) + "\n").encode("utf-8"))
        else:
            serial.write(("kp" + str(event.key_number) + "\n").encode("utf-8"))    
    except Exception:
        console.write(("key event error\n").encode("utf-8"))

rx_buffer = ""
serial.write(("strt").encode("utf-8"))
counter = 0

while True:
    if counter >= 99:
        counter = 0
        serial.write(("hb99\n").encode("utf-8"))
    counter += 1    

    if serial.in_waiting:
        serial.write(("data received\n").encode("utf-8"))
        data = serial.read(serial.in_waiting)
       
        if data:

            rx_buffer += data.decode("utf-8")
            console.write(("Received data: " + str(rx_buffer) + "\n").encode("utf-8"))   
            while "\n" in rx_buffer:
                line, rx_buffer = rx_buffer.split("\n", 1)
                handle_line(line)            
                console.write(("Handled line: " + line + "\n").encode("utf-8"))


    event = macropad.keys.events.get()
    if event and event.pressed:
        handle_key_event(event)

    time.sleep(0.01)

    # # Handle encoder switch presses (debounced)
    # try:
    #     macropad.encoder_switch_debounced.update()
    #     encoder_pressed = macropad.encoder_switch_debounced.pressed
    #     if encoder_pressed and not last_encoder_switch:
    #         # rising edge: encoder was pressed
    #         try:
    #             console.write(("encp\n").encode("utf-8"))
    #         except Exception:
    #             pass
    #     last_encoder_switch = encoder_pressed
    # except Exception:
    #     # If debounced helper isn't available, try simple attribute
    #     try:
    #         enc = getattr(macropad, 'encoder_switch', False)
    #         if enc:
    #             try:
    #                 serial.write(("encp\n").encode("utf-8"))
    #             except Exception:
    #                 pass
    #     except Exception:
    #         pass



    #time.sleep(0.01)

