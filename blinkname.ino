const pin_t MY_LED = D7;

//a dot lasts for one second
const unsigned long dot = 1000;
//a dash last for three seconds
const unsigned long dash = 3000;
//the space between dots and dashes that are part of the same letter is one second
const unsigned long symbolPause = 1000;
//the space between different letters is three seconds
const unsigned long letterPause = 3000;
//the space between different words is seven seconds
const unsigned long wordPause = 7000;

void setup()
{
	pinMode(MY_LED, OUTPUT);
}

String charToMorse(char16_t letter)
{
    switch(letter)
    {
        case 'a': case 'A':
        return ".-"; break;
        case 'b': case 'B':
        return "-..."; break;
        case 'c': case 'C':
        return "-.-."; break;
        case 'd': case 'D':
        return "-.."; break;
        case 'e': case 'E':
        return "."; break;
        case 'f': case 'F':
        return "..-."; break;
        case 'g': case 'G':
        return "--."; break;
        case 'h': case 'H':
        return "...."; break;
        case 'i': case 'I':
        return ".."; break;
        case 'j': case 'J':
        return ".---"; break;
        case 'k': case 'K':
        return "-.-"; break;
        case 'l': case 'L':
        return ".-.."; break;
        case 'm': case 'M':
        return "--"; break;
        case 'n': case 'N':
        return "-."; break;
        case 'o': case 'O':
        return "---"; break;
        case 'p': case 'P':
        return ".--."; break;
        case 'q': case 'Q':
        return "--.-"; break;
        case 'r': case 'R':
        return ".-."; break;
        case 's': case 'S':
        return "..."; break;
        case 't': case 'T':
        return "-"; break;
        case 'u': case 'U':
        return "..-"; break;
        case 'v': case 'V':
        return "...-"; break;
        case 'w': case 'W':
        return ".--"; break;
        case 'x': case 'X':
        return "-..-"; break;
        case 'y': case 'Y':
        return "-.--"; break;
        case 'z': case 'Z':
        return "--.."; break;
        default:
        return "/"; break;
    }
}

String stringToMorse(String input)
{
    String output = "";
    for(int i = 0; i < input.length(); i++)
    {
        if(i!=0)
        {
            output+=" ";
        }
        output += charToMorse(input[i]);
    }
    return output;
}

void blink(unsigned long duration, unsigned long pause)
{
    if(duration > 0)
    {
	digitalWrite(MY_LED, HIGH);
	delay(duration);
	digitalWrite(MY_LED, LOW);
    }
	delay(pause);
    
}

void blinkMorseCode(String name)
{
    String morseCode = stringToMorse(name);
    Particle.publish(morseCode);
    for(int i = 0; i < morseCode.length(); i++)
    {
        unsigned long duration;
        unsigned long pause;
        switch(morseCode[i])
        {
            case '.':
            duration = dot;
            pause = symbolPause; break;
            case '-':
            duration = dash;
            pause = symbolPause; break;
            case ' ':
            duration = 0; 
            pause = letterPause - symbolPause; break;
            default:
            duration = 0;
            pause = wordPause - symbolPause; break;
        }
        blink(duration,pause);
    }
}

void loop()
{
	blinkMorseCode("Jack");
}
