using namespace std;

const int led1 = D7;
//time unit used for spacing
const int timeUnit = 500;
//spacing standards for morse code
const int dot = 1*timeUnit, 
    dash = 3*timeUnit, 
    symbolSpace = 1*timeUnit, 
    letterSpace = (3-symbolSpace/timeUnit)*timeUnit, 
    wordSpace = (7-symbolSpace/timeUnit)*timeUnit;
    
const char letters[27] = { ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o','p', 'q', 'r',
                            's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

const string morseLetters[27] = { " ", ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", 
                                "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--",
                                "--.."};

//put lowercase text into input that you want to translate to morse code
string input = "tripcony";
string morseCode = "";

void setup() 
{
	pinMode(led1, OUTPUT);
	//encrypt the input in morse code
	for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < sizeof(letters)/sizeof(letters[0]); j++)
        {
            if (input[i] == letters[j])
            {
                morseCode += morseLetters[j];
                morseCode += "_";
            }
        }
    }
}

void loop() 
{
    //write the morse code to the led
    for (int i = 0; i < morseCode.size(); i++)
    {
        char symbol = morseCode[i];
        switch (symbol)
        {
            case '.': ledDot(); break;
            case '-': ledDash(); break;
            case '_': delay(letterSpace); break;
            case ' ': delay(wordSpace); break;
            default: ledError();
        }
    }
}

void ledDot()
{
    //method for displaying a dot on the led
    digitalWrite(led1, HIGH);
	delay(dot);
	digitalWrite(led1, LOW);
	delay(symbolSpace);
}

void ledDash()
{
    //method for displaying a dash on the led
	digitalWrite(led1, HIGH);
	delay(dash);
	digitalWrite(led1, LOW);
	delay(symbolSpace);
}

void ledError()
{
    //led sequence to signal an error
    for (int i = 0; i < 50; i++)
    {
        digitalWrite(led1, HIGH);
	    delay(50);
	    digitalWrite(led1, LOW);
	    delay(50);
    }
}
