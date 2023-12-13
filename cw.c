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
        }
    }
    *text_len = b;
    return uniqe_text;
}
//Делим предложения на слова
char** split_sentence(char* sentence, int* word_count)
{
    int c = 0;
    int sentence_len = strlen(sentence);
    int max_words = MEM_STEP;
    char** words = malloc(max_words * sizeof(char*));
    char* copy_of_sentence = strdup(sentence);
    char* token = strtok(copy_of_sentence, ", .");
    while (token != NULL)
    {
        if(c == max_words)
        {
            max_words += MEM_STEP;
            words = realloc(words, max_words * sizeof(char*));
        }
        words[c] = strdup(token);
        token = strtok(NULL, ", ");
        c++;
    }
    free(copy_of_sentence);
    *word_count = c;
    return words;
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
        int word_count = 0;
        char** splited_sentence = split_sentence(new_text[i], &word_count);
        if(word_count % 2 != 0)
        {
            formated_text[c] = strdup(new_text[i]);
            c++;
        }

        for (int j = 0; j < word_count; j++)
        {
            free(splited_sentence[j]);
        }
        free(splited_sentence);
    }
    *text_len = c;
    return formated_text;
}
//Исполнение 3 функции
int isVowel(char c) {
    c = tolower(c);
    return (strchr("aeiou", c) != NULL);
}

int summ_of_vowels(char* sentence1, int sentence_len1)
{
    int c = 0;
    int word_count = 0;
    char** splited_sentence = split_sentence(sentence1, &word_count);
    for(int i = 0; i < sentence_len1; i++)
    {
        if(i % 2 == 0)
        {
            if(isVowel(sentence1[i]))
            {
                c++;               
            }
        }
    }
    return c;
}

int cmp(const void* a, const void* b)
{
    char* first = *(char**)a;
    char* second = *(char**)b;
    int summ_f = summ_of_vowels(first, strlen(first));
    int summ_s = summ_of_vowels(second, strlen(second));
    return summ_s - summ_f;
}

void sort_by_vowels(char** new_text, int* text_len)
{
    qsort(new_text, *text_len, sizeof(char*), cmp);
    for(int i = 0; i < *text_len; i++)
    {
        printf("%s\n", new_text[i]);
    }
}

//Исполнение 4 функции
int all_upper(char* word, int word_len)
{
    int c = 0;
    for(int i = 0; i < word_len; i++)
    {
        if(isupper(word[i]))
        {
            c++;
            if(c == word_len)
            {
                return 1;
            }
        }
    }
    return 0;
}

void print_blue(char** new_text, int* text_len)
{
    for(int i = 0; i < *text_len; i++)
    {
        int c = 0;
        int word_count = 0;
        char** splited_sentence = split_sentence(new_text[i], &word_count);
        if(word_count % 2 != 0)
        {
            for(int j = 0; j < strlen(new_text[i]); j++)
            {
                if (all_upper(splited_sentence[word_count / 2], strlen(splited_sentence[word_count / 2])))
                {
                    if((new_text[i][j] == ' ' || new_text[i][j] == ',') && (new_text[i][j-1] != ' ' && new_text[i][j-1] != ','))
                    {
                    c++;
                    }
                    if((c == word_count / 2 || word_count == 1) && isalnum(new_text[i][j]) && all_upper(splited_sentence[word_count / 2], strlen(splited_sentence[word_count / 2])))
                    {
                        printf("\x1b[34m%c\x1b[0m", new_text[i][j]);
                    }
                    else if(new_text[i][j] == '.')
                    {
                        printf(". ");
                    }
                    else
                    {
                        printf("%c", new_text[i][j]);
                    }
                }
            }
        }
    }
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
    int func_num;
    scanf("%d", &func_num);
    char** text = make_text(&text_len);
    char** new_text = delete_duplicate(text, &text_len);
    switch (func_num)
    {
    case 0:
        print_text(new_text, text_len);
        break;
    case 1:
        char** f_func = f_upper(new_text, &text_len);
        print_text(f_func, text_len);
        break;
    case 2:
        char** s_func = delete_even(new_text, &text_len);
        print_text(s_func, text_len);
        break;
    case 3:
        sort_by_vowels(new_text, &text_len);
        break;
    case 4:
        print_blue(new_text, &text_len);
        break;
    default:
        break;
    }
    return 0;
}