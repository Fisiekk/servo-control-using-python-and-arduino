import pygame #im using pygame 2.0.1
import serial #and pyserial 3.5
import time

def _map(x, inMin, inMax, outMin, outMax):
    return int((x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin) #map() like function in arduino

pygame.init()

ser = serial.Serial('COM4', 115200, timeout=1) #serial init
screen = pygame.display.set_mode((1000, 650)) #create display

running = True

while running:
  pos = pygame.mouse.get_pos()
  send = (str(_map(pos[0], 0, 1000, 0, 180)) + ":" + str(180 - _map(pos[1], 0, 650, 0, 180))).encode() #"making" string and encoding it for serial (string looks like that 180:90, 9:123, 42:15)
  ser.write(bytes(send)) #sendigng string to esp32/arduino
  #print(pos) #debug
  time.sleep(0.1) #wait only to not overload esp32/arduino
  for event in pygame.event.get(): 
    if event.type == pygame.QUIT: #event to close pygame window and python script
      running = False
