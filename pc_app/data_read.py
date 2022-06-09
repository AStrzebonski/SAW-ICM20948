import serial
import atexit


def exit_handler(ser):
    ser.close()

def serial_init(rate, port):
    ser = serial.Serial()
    ser.baudrate = rate
    ser.port = port
    ser.timeout = 1
    ser.parity = serial.PARITY_NONE
    ser.stopbits = serial.STOPBITS_ONE
    ser.bytesize = serial.EIGHTBITS
    ser.open()
    ser.reset_input_buffer()

    atexit.register(exit_handler, ser=ser)
    return ser


def read_data(ser):

    ax = 0; ay = 0; az = 0; ux = 0; uy = 0; uz = 0
    a_read = False
    u_read = False
    while (not a_read) or (not u_read):
        ls = ser.read_until('\\xff\\xff\\xab', 18)
        if ls[3:4]== b'\x02':
            ax = int.from_bytes(ls[6:8], 'little', signed=True)
            ay = int.from_bytes(ls[10:12], 'little', signed=True)
            az = int.from_bytes(ls[14:16], 'little', signed=True)
            a_read = True
        if ls[3:4] == b'\x01':
            ux = int.from_bytes(ls[6:8], 'little', signed=True)
            uy = int.from_bytes(ls[10:12], 'little', signed=True)
            uz = int.from_bytes(ls[14:16], 'little', signed=True)
            u_read = True
    return ax, ay, az, ux, uy, uz
