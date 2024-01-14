from vosk import Model, KaldiRecognizer
import os
import pyaudio
import json
import requests

model_path = '/Users/harshinshah/Downloads/vosk-model-en-us-0.22'  # !Replace with your model path!
if not os.path.exists(model_path):
    print("no model :(")
    exit(1)

model = Model(model_path)


mic = pyaudio.PyAudio()
stream = mic.open(format=pyaudio.paInt16, channels=1, rate=16000, input=True, frames_per_buffer=4096)
stream.start_stream()


recognizer = KaldiRecognizer(model, 16000)

print("Speak now, press Ctrl+C to stop.")


while True:
    data = stream.read(4096, exception_on_overflow = False)
    if recognizer.AcceptWaveform(data):
        
        data_to_send = json.loads(recognizer.Result())['text']
        print(data_to_send)
        requests.get(f'http://10.0.0.1/{data_to_send}_MORSE')
    # else:
    #     print(recognizer.PartialResult())


stream.stop_stream()
stream.close()
mic.terminate()
