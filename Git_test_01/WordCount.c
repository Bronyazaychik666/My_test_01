#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_FILENAME 256
#define BUFFER_SIZE 1024

// 函数声明
void print_usage(const char *program_name);
long count_characters(const char *filename);
long count_words(const char *filename);

int main(int argc, char *argv[]) {
    // 检查参数数量
    if (argc != 3) {
        print_usage(argv[0]);
        return 1;
    }
    
    // 获取参数
    char *parameter = argv[1];
    char *filename = argv[2];
    
    // 检查参数是否为 -c 或 -w
    if (strcmp(parameter, "-c") != 0 && strcmp(parameter, "-w") != 0) {
        printf("错误：参数必须是 -c 或 -w\n");
        print_usage(argv[0]);
        return 1;
    }
    
    // 根据参数执行相应功能
    long result;
    if (strcmp(parameter, "-c") == 0) {
        result = count_characters(filename);
        if (result >= 0) {
            printf("字符数：%ld\n", result);
        } else {
            return 1;
        }
    } else if (strcmp(parameter, "-w") == 0) {
        result = count_words(filename);
        if (result >= 0) {
            printf("单词数：%ld\n", result);
        } else {
            return 1;
        }
    }
    
    return 0;
}

/**
 * 打印使用说明
 */
void print_usage(const char *program_name) {
    printf("使用方法：%s [parameter] [input_file_name]\n", program_name);
    printf("  -c : 统计字符数\n");
    printf("  -w : 统计单词数\n");
    printf("示例：\n");
    printf("  %s -c input.txt\n", program_name);
    printf("  %s -w input.txt\n", program_name);
}

/**
 * 统计文件中的字符数
 * 返回值：字符数，如果出错返回 -1
 */
long count_characters(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("错误：无法打开文件 '%s'\n", filename);
        return -1;
    }
    
    long char_count = 0;
    int ch;
    
    // 逐个字符读取并计数
    while ((ch = fgetc(file)) != EOF) {
        char_count++;
    }
    
    fclose(file);
    return char_count;
}

/**
 * 统计文件中的单词数
 * 单词定义：由空格、逗号、水平制表符、换行符分割的字符序列
 * 返回值：单词数，如果出错返回 -1
 */
long count_words(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("错误：无法打开文件 '%s'\n", filename);
        return -1;
    }
    
    long word_count = 0;
    int ch;
    int in_word = 0;  // 标志：当前是否在单词中
    
    while ((ch = fgetc(file)) != EOF) {
        // 判断当前字符是否为单词分隔符
        // 分隔符包括：空格、逗号、水平制表符、换行符
        if (ch == ' ' || ch == ',' || ch == '\t' || ch == '\n') {
            // 如果之前在单词中，则结束一个单词
            if (in_word) {
                word_count++;
                in_word = 0;
            }
        } else {
            // 非分隔符，表示在单词中
            in_word = 1;
        }
    }
    
    // 如果文件最后还有单词，需要计数
    if (in_word) {
        word_count++;
    }
    
    fclose(file);
    return word_count;
}