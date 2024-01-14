import pyaudio
import numpy as np
from scipy.fft import rfft, rfftfreq
import requests
import time
# from pyfirmata import Arduino

# Constants
CHUNK = 4096  # Number of audio samples per frame
FORMAT = pyaudio.paInt16  # Audio format (16-bit PCM)
CHANNELS = 1  # Single channel for microphone
RATE = 44100  # Sampling rate
threshold = 100000

# port = '/dev/cu.usbmodem14401'
# pin=3
# board = Arduino(port)

def analyze_audio(data, y):
   
    # Convert byte data to numpy array
    audio_data = np.frombuffer(data, dtype=np.int16)
    
    # Fast Fourier Transform
    yf = rfft(audio_data)
    xf = rfftfreq(CHUNK, 1 / RATE)

    # Analyze the frequency components
    if np.any(np.abs(yf[(xf >= 10) & (xf <= 60)]) > threshold):
        print(y)
        requests.get(f'http://10.0.0.1/BUZZ')
        # board.digital[pin].write(1)
        # time.sleep(0.075)
        # board.digital[pin].write(0)

def main():
    p = pyaudio.PyAudio()

    # Open stream
    stream = p.open(format=FORMAT, channels=CHANNELS, rate=RATE, input=True, frames_per_buffer=CHUNK, input_device_index=0)
    y = 0

    try:
        while True:
            data = stream.read(CHUNK, exception_on_overflow = False)
            analyze_audio(data, y)
            y += 1
    except KeyboardInterrupt:
        # Graceful exit on Ctrl-C
        pass
    finally:
        # Close the stream
        stream.stop_stream()
        stream.close()
        p.terminate()

if __name__ == '__main__':
    main()
