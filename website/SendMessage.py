# kirim pesan ke whatsapp
# String apiKey = "27c80793b8a81c66c88222d4eced071de5827853";
# String idDevice = "4829";
# String sender = "6289623426138";

# https://wa.srv15.wapanels.com/send-message?api_key=1234567890&sender=62888xxxx&number=62888xxxx&message=Hello World
import requests

api_key = "27c80793b8a81c66c88222d4eced071de5827853"
sender = "6281364832035"
number = "62895618191161"

class SendMessage:
    def send_whatsapp_message(message):
        url = "https://wa.srv15.wapanels.com/send-message"
        
        payload = {
            "api_key": api_key,
            "sender": sender,
            "number": number,
            "message": message
        }

        response = requests.get(url, params=payload)

        print("URL:", response.url)

        if response.status_code == 200:
            print("HTTP Response code:", response.status_code)
            print(response.json())
        else:
            print(f"HTTP GET request failed, error: {response.status_code}")

