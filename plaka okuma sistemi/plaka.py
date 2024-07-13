import cv2
import tkinter as tk
from tkinter import filedialog
import pytesseract
import re

# tesseract.exe dosyasının bulunduğu dizini belirtin
pytesseract.pytesseract.tesseract_cmd = r"C:\Program Files\Tesseract-OCR\tesseract.exe"


def recognize_plate(frame):
    ...
    text = pytesseract.image_to_string(cropped_image, config='--psm 11')
    ...
    plates = re.findall(r'[A-Z]{2}\s\d{2}\s[A-Z]{1,3}\s\d{3,4}', text)
    if plates:
        return plates[0]
    else:
        return None


def count_cars(frame):
    ...
    return count


def select_video():
    video_path = filedialog.askopenfilename()
    if video_path:
        cap = cv2.VideoCapture(video_path)
        if not cap.isOpened():
            raise IOError("Could not open video")
        fps = cap.get(cv2.CAP_PROP_FPS)
        while True:
            ret, frame = cap.read()
            if ret:
                plate = recognize_plate(frame)
                car_count = count_cars(frame)
                if plate:
                    plate_label.config(text=f"Plaka: {plate}")
                else:
                    plate_label.config(text="Plaka bulunamadı")
                car_count_label.config(text=f"Araç Sayısı: {car_count}")
                cv2.imshow('frame', frame)
                if cv2.waitKey(int(1000/fps)) & 0xFF == ord('q'):
                    break
            else:
                break
        cap.release()
        cv2.destroyAllWindows()


root = tk.Tk()
root.title("Plaka Tanıma Sistemi")
root.geometry("400x200")

select_button = tk.Button(root, text="Video Seç", command=select_video)
select_button.pack(pady=20)

plate_label = tk.Label(root, text="")
plate_label.pack()

car_count_label = tk.Label(root, text="")
car_count_label.pack()

root.mainloop()
