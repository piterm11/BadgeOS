#include "../headers/command.h"

void init_cmd(){
    timer_install();
}
void command_controller()
{
    char cmd[100] = {0};
    char rest[100] = {0};

    trunc(kb_buffer.text, cmd, rest);

    if (strcomp(cmd, "echo") == 0)
    {
        echo(rest);
    }
    else if (strcomp(cmd, "len") == 0)
    {
        length(rest);
    }
    else if (strcomp(cmd, "calc") == 0)
    {
        calc(rest);
    }
    else if (strcomp(cmd, "help") == 0)
    {
        help();
    }
    else if (strcomp(cmd, "clear") == 0)
    {
        cls();
    }
    else if (strcomp(cmd, "controls") == 0)
    {
        controls();
    }
    else if (strcomp(cmd, "history") == 0)
    {
        history();
    }
    else if (strcomp(cmd, "counter") == 0)
    {
        counter(rest);
    }
    else if (strcomp(cmd, "threads") == 0)
    {
        threads(rest);
    }
    else if (strcomp(cmd, "kill") == 0)
    {
        kill(rest);
    }
    else if (strcomp(cmd, "") == 0)
    {
    }
    else if(strcomp(cmd, "test") == 0)
    {
        test();
    }
    else if(strcomp(cmd, "mutex")==0)
    {
        mutex_test();
    }
    else
    {
        print_ln("Unknown command");
    }
}

void help()
{
    print_ln("\tcalc <val1><sign><val2>\t-\tcalculates two values");
    print_ln("\tcounter <name> <pos> \t-\tcounts till 999999.");
    print_ln("\tclear\t\t\t-\tclears user area");
    print_ln("\tcontrols\t\t-\tprints information about hotkeys");
    print_ln("\techo <text>\t\t-\tdisplays text on screen");
    print_ln("\thistory\t\t\t-\tdisplays history of used commands");
    print_ln("\tkill <id>\t\t-\tkills working thread/s");
    print_ln("\tlen <text>\t\t-\tgets length of string");
    print_ln("\ttest\t\t\t-\tshows functionalities of the system");
    print_ln("\tthreads [all]\t\t-\tdisplays all working/all threads");
}
void controls()
{
    print_ln("\tTo change text color use Function Keys.\n\tHolding Shift Key gives you darker variants.\n");
    print("\t\t\tF1 - ");
    print_set_color(WHITE, WHITE);
    print("       ");
    print_set_color(WHITE, BLACK);
    print(" + Shift KEY - (BLACK)");
    print_set_color(WHITE, BLACK);
    print("\n");

    print("\t\t\tF2 - ");
    print_set_color(LIGHT_RED, LIGHT_RED);
    print("       ");
    print_set_color(WHITE, BLACK);
    print(" + Shift KEY - ");
    print_set_color(RED, RED);
    print("       ");
    print_set_color(WHITE, BLACK);
    print("\n");

    print("\t\t\tF3 - ");
    print_set_color(LIGHT_GREEN, LIGHT_GREEN);
    print("       ");
    print_set_color(WHITE, BLACK);
    print(" + Shift KEY - ");
    print_set_color(GREEN, GREEN);
    print("       ");
    print_set_color(WHITE, BLACK);
    print("\n");

    print("\t\t\tF4 - ");
    print_set_color(LIGHT_BLUE, LIGHT_BLUE);
    print("       ");
    print_set_color(WHITE, BLACK);
    print(" + Shift KEY - ");
    print_set_color(BLUE, BLUE);
    print("       ");
    print_set_color(WHITE, BLACK);
    print("\n");

    print("\t\t\tF5 - ");
    print_set_color(YELLOW, YELLOW);
    print("       ");
    print_set_color(WHITE, BLACK);
    print(" + Shift KEY - ");
    print_set_color(BROWN, BROWN);
    print("       ");
    print_set_color(WHITE, BLACK);
    print("\n");

    print("\t\t\tF6 - ");
    print_set_color(PINK, PINK);
    print("       ");
    print_set_color(WHITE, BLACK);
    print(" + Shift KEY - ");
    print_set_color(MAGENTA, MAGENTA);
    print("       ");
    print_set_color(WHITE, BLACK);
    print("\n");

    print("\t\t\tF7 - ");
    print_set_color(LIGHT_CYAN, LIGHT_CYAN);
    print("       ");
    print_set_color(WHITE, BLACK);
    print(" + Shift KEY - ");
    print_set_color(CYAN, CYAN);
    print("       ");
    print_set_color(WHITE, BLACK);
    print("\n");

    print("\t\t\tF8 - ");
    print_set_color(LIGHT_GRAY, LIGHT_GRAY);
    print("       ");
    print_set_color(WHITE, BLACK);
    print(" + Shift KEY - ");
    print_set_color(DARK_GRAY, DARK_GRAY);
    print("       ");
    print_set_color(WHITE, BLACK);
    print("\n");
}
void cls()
{
    clear();
}

void echo(char *text)
{
    print_ln("%s", text);
}

void length(char *text)
{
    print_ln("%d", strlen(text));
}

void calc(char *text)
{
    char a[16] = {0};
    char b[16] = {0};
    char sign;
    int lena = 0, lenb = 0;
    for (size_t i = 0; i < strlen(text); i++)
    {
        if (lena == 0)
        {
            if (text[i] == '-' || text[i] == '+' || text[i] == '/' || text[i] == '*')
            {
                lena = i;
                sign = text[i];
            }
            else if (!is_digit(text[i]))
            {
                print_ln("Incorrect value");
                return;
            }
        }
        else if (lenb == 0)
        {
            if (!is_digit(text[i]))
            {
                print_ln("Incorrect value");
                return;
            }
        }
    }
    lenb = strlen(text) - lena - 1;
    memcpy(a, text, lena);
    memcpy(b, text + lena + 1, lenb);
    float x, y;
    x = atof(a);
    y = atof(b);
    switch (sign)
    {
    case '+':
        add(x, y);
        break;
    case '-':
        sub(x, y);
        break;
    case '*':
        multiply(x, y);
        break;
    case '/':
        divide(x, y);
        break;
    default:
        break;
    }
}
void add(float a, float b)
{
    print_ln("%f", a + b);
}
void sub(float a, float b)
{
    print_ln("%f", a - b);
}
void multiply(float a, float b)
{
    print_ln("%f", a * b);
}
void divide(float a, float b)
{
    if (b == 0)
    {
        print_ln("Cannot divide by 0!");
        return;
    }
    print_ln("%f", a / b);
}

void history()
{
    for (int i = 0; i < kb_buffer.history_size; i++)
    {
        print_ln("%s", kb_buffer.buffer_history[i]);
    }
}

int cr = 0;
int cc = 75;
int counter_tab[5] = {0, 0, 0, 0, 0};
char counter_name[100] = "";
int counter_row = 0;

int test_thread=0;

int counter(char *text)
{
    char pos[2] = "";
    char name[20] = "";
    trunc(text, name, pos);
    int p = 0;
    if (strlen(pos) == 0)
    {
        for (int i = 0; i < 6; i++)
        {
            p = i;
            if (i == 5)
            {
                print_ln("Cannot add next counter, please wait until finish");
                return -1;
            }
            if ((threads_controller.thread[counter_tab[p]].state == RUNNING || threads_controller.thread[counter_tab[p]].state == SLEEPING) && counter_tab[p] != 0)
                continue;
            else
                break;
        }
    }
    else if (!is_digit(pos[0]))
    {
        print_ln("Given value is not a number");
        return -1;
    }
    else
        p = pos[0] - '0' - 1;
    if (p > 4 || p < 0)
    {
        print_ln("Given position is out of range (1-5)");
        return -1;
    }

    __asm__ __volatile__("cli");
    if (strlen(name) == 0)
        memcpy(name, "counter", strlen("counter") + 1);
    memcpy(counter_name, name, strlen(name) + 1);
    counter_row = p;
    counter_tab[p] = start_thread((uint32_t)counting, "timer");
    __asm__ __volatile__("sti");
    cr = p + 1;
    if (cr > 4)
        cr = 0;
    return counter_tab[p];
}
void counting()
{
    int row = 0;
    int offset = 5;
    char name[100] = "";
    __asm__ __volatile__("cli");
    row = counter_row;
    memcpy(name, counter_name, strlen(counter_name) + 1);
    __asm__ __volatile__("sti");
    int len = strlen(name) > 10 ? 10 : strlen(name);
    for (int i = 0; i < 15; i++)
    {
        put_at(' ', cc + i - 10, row);
    }
    for (int i = 0; i < len; i++)
    {
        put_at(name[i], cc + i - 10, row);
    }
    int time = 1;
    while (time <= 99999)
    {
        __asm__ __volatile__("cli");
        for (int i = 0; i < 5; i++)
        {
            put_at(' ', cc + i, row);
        }
        char t[20] = {0};
        itoa(time, t);
        for (int i = 0; i < strlen(t); i++)
        {
            put_at(t[i], cc + i + (offset - strlen(t)), row);
        }
        __asm__ __volatile__("sti");
        scheduler();
        sleep(1);
        time++;
    }
}

void threads(char *text)
{
    if(strcomp(text,"all")==0)
        display_all_threads();
    else
        display_threads();
}

void _kill(int8_t id)
{
    if (id > THREAD_COUNT)
        return;
    if(threads_controller.thread[id].state == TERMINATED)
    return;
    if (id == 0)
    {
        print_ln("Cannot kill the clock");
        return;
    }
    int t =0;
    
    while(threads_controller.thread[t].next_thread_id!=id)
    {
        t=threads_controller.thread[t].next_thread_id;
    }
    threads_controller.thread[t].next_thread_id = threads_controller.thread[id].next_thread_id;
    threads_controller.thread[id].state = TERMINATED;
    threads_controller.no_active_threads--;
    
    scheduler();
}
void kill(char *text)
{
    if(strcomp(text, "") == 0)
        return;
    else
    {
        for (size_t i = 0; i < strlen(text); i++)
        {
            if (!is_digit(text[i]))
            {
                print_ln("Incorrect value");
                return;
            }
        }
        int id = atoi(text);
        _kill(id);
    }
}


void test()
{
    __asm__ __volatile__("cli");
    test_thread=start_thread((uint32_t)testing, "test");
    __asm__ __volatile__("sti");
}
void testing(){
    kbd_off();
    print_ln("Hello, this is test of BadgeOS!");
    sleep(2000);
    cls();
    sleep(500);
    print_ln("Calc command with examples\n>calc 2+1");
    calc("2+1");
    sleep(500);
    print_ln("\n>calc 31/0");
    calc("31/0");
    sleep(2000);
    print_ln("\nCounter command with example\n>counter test 3");
    int c = counter("test 3");
    print_ln("\nAs you can see counter appears at top right corner.");
    sleep(2000);
    print_ln("\nTo stop counter we need to check currently working threads and find correct thread\n>threads");
    threads("");
    sleep(2000);
    print_ln("\nThere are %d threads, first one is always system clock,which is unkillable.",threads_controller.no_active_threads);
    sleep(2000);
    print_ln("\nOkay, it's time to stop counter\n>kill %d",c);
    char text[10]={0};
    itoa(c,text);
    kill(text);
    sleep(2000);
    print_ln("\nClear command:\n>clear");
    sleep(500);
    cls();
    sleep(500);
    print_ln("Echo command with example:\n>echo This is test");
    echo("This is test");
    sleep(2000);
    print_ln("\nLen command with example\n>len qwerty 123454");
    length("qwerty 123454");
    sleep(2000);
    print_ln("\nMutex test:");
    mutex_test();
    print_ln("\nThat's the end of the test. Try BadgeOS for your own!");
    print(">");
    kbd_on();
}
mutex_t m;
int32_t v=0;
void mutex_test()
{
    __asm__ __volatile__("cli");
    int a =start_thread((uint32_t)_mutex_test, "mutex 1");
    int b =start_thread((uint32_t)_mutex_test, "mutex 2");
    __asm__ __volatile__("sti");
    sleep(1000);
    print_ln("if not 0 there is a problem: %d",v);
    _kill(a);
    _kill(b);
}

void _mutex_test()
{
    for (int i = 0;  i < 100000; i++){
		for (int j = 0;  j <100000; j++){
			mutex_lock(&m);
			v++; v++; v++; v++; v++;
            v--; v--; v--; v--; v--;
            v++; v++; v++; v++; v++;
            v--; v--; v--; v--; v--;
            v++; v++; v++; v++; v++;
            v--; v--; v--; v--; v--;
            v++; v++; v++; v++; v++;
            v--; v--; v--; v--; v--;
			mutex_unlock(&m);
		}
	}
}