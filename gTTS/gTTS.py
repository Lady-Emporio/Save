import time
# from gtts import gTTS
# mp3_name = "1.mp3"
# x="Отдел продаж."
# tts=gTTS(text=x, lang='ru')
# tts.save(mp3_name)
def Play(mp3_name):
	mixer.music.load(mp3_name)
	mixer.music.play()
	while mixer.music.get_busy():
		time.sleep(0.1)

from pygame import mixer
Start="SaleDir.mp3"
Name=["Alexandr.mp3","Nicolay.mp3","Victor.mp3"]
Nomber=["","Nomber//1.mp3","Nomber//2.mp3","Nomber//3.mp3"]
mixer.init()
# mixer.music.load(mp3_name)
# mixer.music.play()
# while mixer.music.get_busy():
# 	time.sleep(0.1)
Play(Start)
Play(Name[2])
Play(Nomber[1])
Play(Name[0])
Play(Nomber[2])
Play(Name[1])
Play(Nomber[3])