#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MEM_STEP 10
#define END_OF_STRING '\n'


void print_CW_info()
{
    printf("Course work for option 4.1, created by Ivan Rodnov\n");
}
//Посимвольный ввод текста
char* get_sentence()
{
    int size = MEM_STEP;
    char* sentence = malloc(size*sizeof(char));
    int sentence_len = 0;
    char temp_char;
    do
    {
        temp_char = getchar();
        // ?
        if(sentence_len == 0 && temp_char == ' ')
        {
            continue;
        }
        else
        {
            sentence[sentence_len] = temp_char;
            sentence_len++;
            if(sentence_len == size - 1)
            {
                size += MEM_STEP;
                sentence = realloc(sentence, sizeof(char) * size);
            }
        }
    } while (temp_char != '.' && temp_char != END_OF_STRING);
    sentence[sentence_len] = '\0';
    return sentence;
}

char** make_text(int* text_len){
    int size = MEM_STEP;
    char** text = malloc(size * sizeof(char*));
    int local_text_len = 0;
    int nl_count = 0;
    char* temp_sentence;
    do
    {
        temp_sentence = get_sentence();
        int len = strlen(temp_sentence);
        if (len > 0 && temp_sentence[len - 1] == END_OF_STRING)
        {
            nl_count++;
        }
        else
        {
            nl_count = 0;
            text[local_text_len] = temp_sentence;
            local_text_len++;
        }
        
    } while(nl_count < 2);
    *text_len = local_text_len;
    return text;
}

//Удаление одинаковых предложений
int comp_letters(char f, char s) {
    if ((isdigit(f) && isdigit(s) && f != s) ||
        (isalpha(f) && isalpha(s) && toupper(f) != toupper(s)) ||
        (!isalnum(f) && !isalnum(s) && f != s))
    {
        return 0;
    }
    return 1;
}

int comp_str(char* f, char* s)
{
    int f_len = strlen(f);
    int s_len = strlen(s);
    if(f_len != s_len)
    {
        return 0;
    }
    else
    {
        for(int i = 0; i < f_len; i++)
        {
            if(comp_letters(f[i], s[i]) == 0)
            {
                return 0;
            }
        }
    }
    return 1;   
}

char** delete_duplicate(char** text, int* text_len)
{
    int *check_arr = calloc(*(text_len), sizeof(int));
    char** uniqe_text = malloc(*(text_len) * sizeof(char*));
    for(int i = 0; i < *text_len; i++)
    {
        for(int j = i+1; j < *text_len; j++)
        {
            if(comp_str((text)[i], (text)[j]) == 1)
            {
                check_arr[j] = 1;
                printf("%s %s %d %d %d\n", text[i], text[j], i,j,check_arr[j]);
            }
        }
    }
    int b = 0;
    for(int i = 0; i < *text_len; i++)
    {
        if(check_arr[i] == 0)
        {
            uniqe_text[b] = text[i];
            b++;
            printf("uniqe\n");
        }
        else
        {
            printf("not uniqe\n");
        }
    }
    *text_len = b;
    return uniqe_text;
}

//Исполнение 1 задачи
char** f_upper(char** new_text, int* text_len)
{
    for(int i = 0; i < *text_len; i++)
    {
        int str_len = strlen(new_text[i]);
        for(int j = 0; j < str_len; j++)
        {
            if(j == 0)
            {
                new_text[i][j] = toupper(new_text[i][j]);
            }
            else
            {
                new_text[i][j] = tolower(new_text[i][j]);
            }
        }
    }
    return new_text;
}
//Исполнение 2 функции
char** delete_even(char** new_text, int* text_len)
{
    char** formated_text = malloc(*text_len * sizeof(char*));
    int c = 0;
    for(int i = 0; i < *text_len; i++)       
    {
        int str_len = strlen(new_text[i]);
        if(str_len % 2 != 0)
        {
            formated_text[c] = new_text[i];
            c++;
        }
    }
    *text_len = c;
    return formated_text;
}

//Вывод
void print_text(char** text, int text_len)
{
    for (int i = 0; i < text_len; i++)
    {
        printf("%s\n", text[i]);
    }
}

int main(void)
{
    print_CW_info();
    int text_len = 0;
    char** text = make_text(&text_len);
    char** new_text = delete_duplicate(text, &text_len);
    char** f_func = f_upper(new_text, &text_len);
    print_text(f_func, text_len);
    char** s_func = delete_even(new_text, &text_len);
    for (int i = 0; i < text_len; i++)
    {
        free(text[i]);
    }
    free(text);

    return 0;
}
