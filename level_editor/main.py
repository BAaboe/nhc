# Based on code from: http://pygametutorials.wikidot.com/tutorials-basic

import pygame
from pygame.locals import *


class App:
    def __init__(self):
        self.mouse_pos = (0,0)
        self.blockSize = 50

        self._running = True
        self._display_surf = None
        self.size = self.width, self.height = 800, 600
        self.level = {"start_pos": [0,0],
                      "data": [],
                      "goal": [0, 0]}
        self.firstRect = None

    def on_init(self):
        pygame.init()
        self._display_surf = pygame.display.set_mode(self.size, pygame.HWSURFACE)
        self._running = True

        pygame.mouse.set_visible(True)

        self.cobel = pygame.image.load("assets/cobel.jpg")
        
        self.cobel = pygame.transform.scale(self.cobel, (self.blockSize, self.blockSize))

        self.gridPos = (int(self.mouse_pos[0]/self.blockSize)*self.blockSize,
                         int(self.mouse_pos[1]/self.blockSize)*self.blockSize)

    def on_event(self, event):
        if event.type == pygame.QUIT:
            self._running = False
        if event.type == pygame.MOUSEBUTTONDOWN:
            if pygame.mouse.get_pressed()[0]:
                rect = [self.gridPos[0], self.gridPos[1], self.blockSize, self.blockSize]
                if not self.firstRect:
                    if rect not in self.level["data"]:
                        self.firstRect = rect
                else:
                    x = self.firstRect[0]
                    y = self.firstRect[1]
                    width = rect[0]+rect[2]-self.firstRect[0]
                    height = rect[1]+rect[3]-self.firstRect[1]
                    
                    if self.firstRect[0] < rect[0]:
                        x = self.firstRect[0]
                        width = rect[0]+rect[2]-self.firstRect[0]
                    else:
                        x = rect[0]
                        width = self.firstRect[0]+self.firstRect[2]-rect[0]

                    if self.firstRect[1] < rect[1]:
                        y = self.firstRect[1]
                        height = rect[1]+rect[3]-self.firstRect[1]
                    else:
                        y = rect[1]
                        height = self.firstRect[1]+self.firstRect[3]-rect[1]

                    bigRect = [x, y, width, height]
                    self.level["data"].append(bigRect)
                    self.firstRect = None

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_p:
                print(self.level)
            elif event.key == pygame.K_s:
                las = LoadAndSave()
                self.level = las.sort(self.level)
            elif event.key == pygame.K_ESCAPE:
                self.firstRect = None

    def on_loop(self):
        self.mouse_pos = pygame.mouse.get_pos()
        self.gridPos = (int(self.mouse_pos[0]/self.blockSize)*self.blockSize,
                         int(self.mouse_pos[1]/self.blockSize)*self.blockSize)
        if pygame.mouse.get_pressed()[0]:
            pass

    def on_render(self):
        self._display_surf.fill((255,255,255))
        if self.firstRect == None:
            self._display_surf.blit(self.cobel, self.gridPos)
        else:
            rect = [self.gridPos[0], self.gridPos[1], self.blockSize, self.blockSize]
            
            x = self.firstRect[0]
            y = self.firstRect[1]
            width = rect[0]+rect[2]-self.firstRect[0]
            height = rect[1]+rect[3]-self.firstRect[1]
            
            if self.firstRect[0] < rect[0]:
                x = self.firstRect[0]
                width = rect[0]+rect[2]-self.firstRect[0]
            else:
                x = rect[0]
                width = self.firstRect[0]+self.firstRect[2]-rect[0]

            if self.firstRect[1] < rect[1]:
                y = self.firstRect[1]
                height = rect[1]+rect[3]-self.firstRect[1]
            else:
                y = rect[1]
                height = self.firstRect[1]+self.firstRect[3]-rect[1]
            
            bigRect = [x, y, width, height]
            self.display_rect(bigRect)

        for rect in self.level["data"]:
            self.display_rect(rect)
        pygame.display.flip()
    
    def display_rect(self, rect):
        for i in range(int(rect[2]/self.blockSize)):
            for j in range(int(rect[3]/self.blockSize)):
                dRect = [rect[0]+i*self.blockSize, rect[1]+j*self.blockSize, self.blockSize, self.blockSize]
                self._display_surf.blit(self.cobel, dRect)
    
    def on_cleanup(self):
        pygame.quit()

    def on_execute(self):
        if self.on_init() == False:
            self._running = False

        while self._running:
            for event in pygame.event.get():
                self.on_event(event)

            self.on_loop()
            self.on_render()

        self.on_cleanup()


class LoadAndSave:
    def __init__(self):
        pass

    def sort(self, level):
        for i in level["data"]:
            for j in range(len(level["data"])):
                if j == len(level["data"])-1:
                    break
                if level["data"][j] > level["data"][j+1]:
                    first = level["data"][j]
                    level["data"][j] = level["data"][j+1]
                    level["data"][j+1] = first
        return level


if __name__ == "__main__":
    levelEditor = App()
    levelEditor.on_execute()
