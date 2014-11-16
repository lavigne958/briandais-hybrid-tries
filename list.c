//
//  list.c
//  Dictionary
//
//  Created by dikov on 09/11/14.
//  Copyright (c) 2014 dikov. All rights reserved.
//

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

struct ListOfWords{
    char* word;
    struct ListOfWords* next;
};

struct ListOfWords* create_non_empty_list(char* word){
    int len = (int)strlen(word);
    struct ListOfWords* list = malloc(sizeof(struct ListOfWords));
    list->word = malloc(len*sizeof(char));
    memset(list->word, 0, len);
    for (int i=0; i<len; i++) {
        list->word[i] = word[i];
    }
    list->next = NULL;
    return list;
}

struct ListOfWords* create_empty_list(){
    struct ListOfWords* list = malloc(sizeof(struct ListOfWords));
    list->word = NULL;
    list->next = NULL;
    return list;
}

char* get_word(struct ListOfWords* list){
    if (list != NULL) {
        return list->word;
    }
    return NULL;
}

void set_word(struct ListOfWords* list, char* word){
    if (list != NULL) {
        strcpy(list->word, word);
    }
}

struct ListOfWords* get_next(struct ListOfWords* list){
    if (list != NULL) {
        return list->next;
    }
    return NULL;
}

bool is_empty_list(struct ListOfWords* list){
    if (list == NULL ||
        (list->word == NULL && list->next == NULL)) {
        return true;
    }
    return false;
}

bool is_word_contained_list(struct ListOfWords* list, char* word){
    while (!is_empty_list(list) || word[0] == '\0') {
        if (!strcmp(list->word, word)) {
            return true;
        }
        list = list->next;
    }
    return false;
}

struct ListOfWords* complex_insert_word_list(struct ListOfWords* list, char* new_word){
    if (new_word[0] == '\0') {
        return list;
    }
    if (list == NULL) {
        list = create_non_empty_list(new_word);
        return list;
    }
    int len = (int)strlen(new_word);
    if (len < strlen(list->word)) {
        struct ListOfWords* new_member = create_non_empty_list(new_word);
        new_member->next = list;
        return new_member;
    }
    struct ListOfWords* head = list;
    struct ListOfWords* previous = NULL;
    if (len == strlen(list->word)) {
        for (int i=0; new_word[i] != '\0'; i++) {
            while (!is_empty_list(list) &&
                   new_word[i] > list->word[i]) {
                previous = list;
                list = list->next;
                if (is_empty_list(list) || len < strlen(list->word)) {
                    struct ListOfWords* new_member = create_non_empty_list(new_word);
                    previous->next = new_member;
                    new_member->next = list;
                    return head;
                }
            }
            if (!is_empty_list(list) && new_word[i] == list->word[i]) {
                if (!strcmp(new_word, list->word)) {
                    return head;
                }
                continue;
            }else{
                break;
            }
        }
        struct ListOfWords* new_member = create_non_empty_list(new_word);
        if (previous == NULL) {
            new_member->next = list;
            head = new_member;
        }else{
            previous->next = new_member;
            new_member->next = list;
        }
        return head;
    }
    while (len > strlen(list->word)) {
        previous = list;
        list = list->next;
        if (is_empty_list(list)) {
            struct ListOfWords* new_member = create_non_empty_list(new_word);
            previous->next = new_member;
            new_member->next = list;
            return head;
        }
    }
    previous->next = complex_insert_word_list(list, new_word);
    return head;
}

struct ListOfWords* simple_insert_word_list(List list, char* new_word){
    if (new_word[0] == '\0') {
        return list;
    }
    if (is_empty_list(list)) {
        return create_non_empty_list(new_word);
    }
    struct ListOfWords* head = list;
    while (list->next != NULL) {
        list = list->next;
    }
    struct ListOfWords* new_member = create_non_empty_list(new_word);
    list->next = new_member;
    return head;
}

