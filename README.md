# TemperatureMeter
This is my first electronics project. 

I built a device that measures the room's temperature and humidity and displays it on a small 
screen.

I know my code is ugly and everything isn't 100% correct. I built this with my own two hands. I 
didn't use any AI for programming and tried to stick to traditional forums and Youtube videos if 
I didn't understand concepts.

I really enjoyed the process. Debugging is something that I really missed since I started using LLMs. 
Using Autodesk fusion for the first time in a few years was also really fun.

I used the Platformio VSCode extension to build the code and flash it onto the esp8266. I used wokwi to simulate the project before I actually built it.

<figure>
    <img width="1008" height="1344" alt="IMG_5780" src="https://github.com/user-attachments/assets/2bd06ee9-9c3a-4697-b8c4-df8183e87bd0" />
    <figcaption>Me testing that all the pins work correctly after soldering onto the board</figcaption>
</figure>

<figure>
    <img width="1008" height="1344" alt="IMG_5783" src="https://github.com/user-attachments/assets/d63aed78-9d91-44ca-8f5c-e3affffe3570" />
    <figcaption>First run after flashing... not everything worked, I was using some dangerous pins (15), that causes boot to fail if pulled high (which I think I did, since my buttons use a pullup resistor).</figcaption>
</figure>

<figure>
    <img width="1008" height="1344" alt="IMG_5788" src="https://github.com/user-attachments/assets/cd7d0454-c8de-4f8c-a964-2a2e99ac1391" />
    <figcaption>First time working!!!</figcaption>
</figure>

## Citations
- [Converting images to bitmaps](https://javl.github.io/image2cpp/)
- [Drawing animations](https://www.pixilart.com/)
- Designing snap fit joints:
    - https://formlabs.com/global/blog/designing-3d-printed-snap-fit-enclosures/
    - https://www.hubs.com/knowledge-base/how-design-snap-fit-joints-3d-printing/#what-are-common-problems-with-designing-snap-fit-joints

- Where I did use AI (Mostly ChatGPT)
    - If I wanted to know more and couldn't find resources online:
        - Understanding some of the module implementation code
    - Converting weird file formats to `stl` so I can import it into fusion 360 to design the case
