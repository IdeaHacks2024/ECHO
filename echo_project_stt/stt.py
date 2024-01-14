import speech_recognition as sr
import serial
import requests

#  for sending strings from python to arduino
arduino_port = 'COM4'
ser = serial.Serial(arduino_port, 9600, timeout=1)
data_to_send = " "


def recognize_speech_from_mic(recognizer, microphone):
    """Transcribe speech from recorded from `microphone`.

    Returns a dictionary with three keys:
    "success": a boolean indicating whether or not the API request was
               successful
    "error":   `None` if no error occured, otherwise a string containing
               an error message if the API could not be reached or
               speech was unrecognizable
    "transcription": `None` if speech could not be transcribed,
               otherwise a string containing the transcribed text
    """
    # Check that recognizer and microphone arguments are appropriate type
    if not isinstance(recognizer, sr.Recognizer):
        raise TypeError("`recognizer` must be `Recognizer` instance")

    if not isinstance(microphone, sr.Microphone):
        raise TypeError("`microphone` must be `Microphone` instance")

    # Adjust the recognizer sensitivity to ambient noise and record audio
    with microphone as source:
        recognizer.adjust_for_ambient_noise(source)
        audio = recognizer.listen(source, timeout=1, phrase_time_limit=3)

    # Set up the response object
    response = {
        "success": True,
        "error": None,
        "transcription": None
    }

    # Try to recognize the speech in the recording
    try:
        response["transcription"] = recognizer.recognize_google(audio)
    except sr.RequestError:
        # API was unreachable or unresponsive
        response["error"] = "API unavailable"
        response["success"] = False
    except sr.UnknownValueError:
        # Speech was unintelligible
        response["error"] = "Unable to recognize speech"

    return response

# Create recognizer and mic instances
recognizer = sr.Recognizer()
microphone = sr.Microphone()

print("A continuous speech recognition system. Speak into the microphone. Press Ctrl+C to exit.")

# Continuously listen and print the transcribed text
while True:
    result = recognize_speech_from_mic(recognizer, microphone)

    if not result["success"]:
        if result["error"] is not None:
            print("ERROR: {}".format(result["error"]))
        continue

    if result["transcription"] is not None:
        print("You said: {}".format(result["transcription"]))
        data_to_send = format(result["transcription"])

        requests.get(f'http://10.0.0.1/{data_to_send}_MORSE')
        # ser.write(data_to_send.encode())

