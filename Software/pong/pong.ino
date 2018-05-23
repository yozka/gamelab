#include <Wire.h> //библиотека двухпроводного интерфеса
#include <Adafruit_SSD1306.h> //библиотека экрана

Adafruit_SSD1306 display;//экран

const int TrimLeft    = A0; //
const int TrimRight   = A3;
const int ButLeft     = PB4; //кнопки
const int ButRigth    = PB3;

int scoreA = 0; //очки игрока А
int scoreB = 0; //очки игрока Б

float x = 0; //положение мячика
float y = 0;
float dx = 0.5f; //направление движения мячика
float dy = 0.25f; //онаже скорость

float Ar = 0; //положение ракетки игрока А
float Br = 0; //положение ракетки игрока Б
float As = 10; //размер ракетки игрока А
float Bs = 10; //размер ракетки игрока Б

void setup()   
{                
    Wire.begin(); //настройка интерфеса
	//настройка экрана
    display.begin(SSD1306_SWITCHCAPVCC,  0x3C);   
    display.clearDisplay();
    display.display(); //показываем экран
	//настраиваем кнопки
    
    pinMode(TrimLeft,   INPUT);
    pinMode(TrimRight,  INPUT);
    pinMode(ButLeft,    INPUT_PULLUP);
    pinMode(ButRigth,   INPUT_PULLUP);

    newGame();//новая игра
}
//функция новой игры
void newGame()
{
    x = 64; //начальное положение мяча
    y = 16;
    dx = 0.5f;
    dy = 0.25f;

    if (rand() % 2 == 0)
    {
        dx = -dx; //меняем тракторию движения меча
    }
    if (rand() % 2 == 0)
    {
        dy = -dy; //меняем тракторию движения меча
    }


    delay(1000);
}
//функция, выиграл игрок А
void winA()
{
    scoreA++; //увеличим очки
    newGame(); //запустим новую игру
}
//ффункция выиграл игрок Б
void winB()
{
    scoreB++;//увеличим очки игрока Б
    newGame();//запустим новую игру
}

void speedUp()
{
    dx = dx * 1.2f;
    dy = dy * 1.2f;
  
}

void loop() 
{
    display.clearDisplay(); //стираем изображения экрана
    display.drawPixel(x, y, WHITE);//рисуем мяч
	//рисуем ракетку игрока А слевой стороны
    display.drawLine(5, Ar, 5, Ar + As, WHITE);
	//рисуем ракетку игрока Б справой стороны
    display.drawLine(122, Br, 122, Br + Bs, WHITE);
	//рисуем количество очков
    display.setTextSize(1); //размер текста 
    display.setTextColor(WHITE); //цвет текста
    display.setCursor(56,0);//кордината вывода текса
    display.print(scoreA);//рисуем очки игрока А
    display.print(":");
    display.print(scoreB); //очки игрока Б
    display.display(); //выводим изображеие на экран
    //столкновения
	  
	  //об ракетку игрока А
    if (x <= 6 && y > Ar && y < Ar + As)
    {
        dx = abs(dx); //изменим движение мяча
        x = 6;
        speedUp();
    }
	  //столкновения об ракетки игрока Б
    if (x >= 121 && y > Br && y < Br + Bs)
    {
        dx = -abs(dx);
        x = 121;
        speedUp();
    }

	//двигаем мяч
    x += dx;
    y += dy;
    if (x < 0)
    {
        winB(); 
    }
    if (x > 127)
    {
        winA();
    }
    //столкновения об верхнию и нижнию стенку
    if (y < 0)
    {
        dy = abs(dy);
        y = 0;
    }
    if (y > 32)
    {
        dy = -abs(dy);
        y = 32;
    }


    const auto left = analogRead(TrimLeft);
    Ar = map(left,  1000, 50, 0, 32 - As);
    
    const auto right = analogRead(TrimRight);
    Br = map(right, 1000, 50, 0, 32 - Bs);


}
