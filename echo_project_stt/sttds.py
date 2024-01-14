from vosk import Model, KaldiRecognizer
import os
import pyaudio
import numpy as np
from scipy.fft import rfft, rfftfreq
import requests
from pyfirmata import Arduino

# From bassDeector.py

# Constants
CHUNK = 16384  # Number of audio samples per frame
FORMAT = pyaudio.paInt16  # Audio format (16-bit PCM)
CHANNELS = 1  # Single channel for microphone
RATE = 44100  # Sampling rate
threshold = 100000

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
    # Speech-to-text model
    model_path = '/Users/harshinshah/Downloads/vosk-model-en-us-0.22'  # !Replace with your model path!
    if not os.path.exists(model_path):
        print("no model :(")
        exit(1)

    model = Model(model_path)

    recognizer = KaldiRecognizer(model, 16000)

    p = pyaudio.PyAudio()

    # Open stream
    stream = p.open(format=FORMAT, channels=CHANNELS, rate=RATE, input=True, frames_per_buffer=CHUNK, input_device_index=0)
    y = 0

    print("Speak now, press Ctrl+C to stop.")


    try:
        while True:
            data = stream.read(CHUNK, exception_on_overflow = False)
            analyze_audio(data, y)
            if recognizer.AcceptWaveform(data):
                print(recognizer.Result())
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


# mic = pyaudio.PyAudio()
# stream = mic.open(format=pyaudio.paInt16, channels=1, rate=16000, input=True, frames_per_buffer=4096)
# stream.start_stream()



# while True:
#     data = stream.read(4096)
#     if recognizer.AcceptWaveform(data):
#         print(recognizer.Result())
    # else:
    #     print(recognizer.PartialResult())


# stream.stop_stream()
# stream.close()
# mic.terminate()
