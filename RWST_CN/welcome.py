# 版权所有 睿集团 2020。保留所有权利。
# 仅供学习或RWST出现问题的时候重新编译。
# 请不要进行修改后私有化，否则我们会追究法律责任。
# 用户隐私协议见 "RWSTINSDIR\user\UPA.txt" 或在RWST里输入 "UPA"。

import pygame
import sys
import os
from pygame.locals import *

pygame.init()
pygame.mixer.init()
screen=pygame.display.set_mode((800, 600))
pygame.display.set_caption("欢迎使用 RWST")

i=0
key=0
while True:
    for event in pygame.event.get():
        if event.type in (QUIT, KEYDOWN):
            sys.exit()
    screen.fill((30,30,30))
    if key == 0:
        pygame.time.delay(80)
        i+=1
        if i == 1:background=pygame.image.load(r".\bg\0\1.png").convert()
        elif i == 2:background=pygame.image.load(r".\bg\0\2.png").convert()
        elif i == 3:background=pygame.image.load(r".\bg\0\3.png").convert()
        elif i == 4:background=pygame.image.load(r".\bg\0\4.png").convert()
        elif i == 5:background=pygame.image.load(r".\bg\0\5.png").convert()
        elif i == 6:
            pygame.time.delay(800)
            background=pygame.image.load(r".\bg\0\6.png").convert()
        elif i == 7:
            pygame.time.delay(500)
            background=pygame.image.load(r".\bg\0\7.png").convert()
        elif i == 8:
            pygame.time.delay(500)
            key+=1
            i=0
        screen.blit(background,(0,0))
    elif key == 1:
        background=pygame.image.load(r".\bg\1\1.png").convert()
        screen.blit(background,(0,0))
        x,y=pygame.mouse.get_pos()
        if y>=438 and y<=502 and x>=318 and x<=482 and event.type == pygame.MOUSEBUTTONDOWN:
            pygame.time.delay(300)
            key+=1
    elif key == 2:
        background=pygame.image.load(r".\bg\1\2.png").convert()
        screen.blit(background,(0,0))
        x,y=pygame.mouse.get_pos()
        if y>=438 and y<=502 and x>=318 and x<=482 and event.type == pygame.MOUSEBUTTONDOWN:
            pygame.time.delay(300)
            key+=1
    elif key == 3:
        background=pygame.image.load(r".\bg\1\3.png").convert()
        screen.blit(background,(0,0))
        x,y=pygame.mouse.get_pos()
        if y>=438 and y<=502 and x>=318 and x<=482 and event.type == pygame.MOUSEBUTTONDOWN:
            pygame.time.delay(300)
            key+=1
    elif key == 4:
        background=pygame.image.load(r".\bg\1\4.png").convert()
        screen.blit(background,(0,0))
        x,y=pygame.mouse.get_pos()
        if y>=438 and y<=502 and x>=318 and x<=482 and event.type == pygame.MOUSEBUTTONDOWN:
            pygame.time.delay(300)
            key+=1
    elif key == 5:
        background=pygame.image.load(r".\bg\1\5.png").convert()
        screen.blit(background,(0,0))
        x,y=pygame.mouse.get_pos()
        if y>=438 and y<=502 and x>=318 and x<=482 and event.type == pygame.MOUSEBUTTONDOWN:
            pygame.time.delay(300)
            key+=1
    elif key == 6:
        background=pygame.image.load(r".\bg\1\6.png").convert()
        screen.blit(background,(0,0))
        x,y=pygame.mouse.get_pos()
        if y>=438 and y<=502 and x>=318 and x<=482 and event.type == pygame.MOUSEBUTTONDOWN:
            pygame.time.delay(300)
            key+=1
            break
    pygame.display.update()

os.system("start .\\RWST.exe")