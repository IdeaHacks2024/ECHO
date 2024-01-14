import pyaudio
import numpy as np
from scipy.fft import rfft, rfftfreq
import requests

# Constants
CHUNK = 16384  # Number of audio samples per frame
FORMAT = pyaudio.paInt16  # Audio format (16-bit PCM)
CHANNELS = 1  # Single channel for microphone
RATE = 44100  # Sampling rate
threshold = 90000



def analyze_audio(data, y):
   
    # Convert byte data to numpy array
    audio_data = np.frombuffer(data, dtype=np.int16)
    
    # Fast Fourier Transform
    yf = rfft(audio_data)
    xf = rfftfreq(CHUNK, 1 / RATE)

    # Analyze the frequency components
    if np.any(np.abs(yf[(xf >= 20) & (xf <= 80)]) > threshold):
        print(y)
        temp = requests.get(f'http://10.0.0.1/BUZZ')

def main():
    p = pyaudio.PyAudio()

    # Open stream
    stream = p.open(format=FORMAT, channels=CHANNELS, rate=RATE, input=True, frames_per_buffer=CHUNK)
    y = 0

    try:
        while True:
            data = stream.read(CHUNK)
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
