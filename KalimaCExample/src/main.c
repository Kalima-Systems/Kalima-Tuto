#define CLONELIB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "callback.h"

void Menu();
void send_10_messages(Node *node);
void send_modulable_message(Node *node);

int main() {
    int choice = 0, end = 0;
    Node *node = create_Node("etc/cfg/config.txt", NULL);
    if(node == NULL){
        printf("Error creating Node. Please verify the config file\n");
        return 0;
    } 
    printf("Config loaded\n");
    ClientCallback* callback = set_callback();
    Connect_to_Notaries(node, callback);
    sleep(2);
    printf("GO!\n");
    Menu();
    while(end == 0){
        scanf("%d", &choice);
        if ( choice == 1) {
            send_10_messages(node);
        } else if (choice == 2) {
            send_modulable_message(node);
        } else if (choice == 3) {
            end = 1;
        }
    }
}

void Menu() {
  printf( "commands available :\n" );
  printf( "- 1 ==> Send 10 messages\n" );
  printf( "- 2 ==> Send a modulable message\n" );
  printf( "- 3 ==> Close\n" );
}

void send_10_messages(Node *node){
    for(int i=0 ; i<10 ; i++) {
        uint8_t body_size = get_int_len(95+i);
        char body[body_size];
        snprintf(body, body_size+1, "%d", 95+i);
        char key[13];
        snprintf(key, 13, "%s%d", "temperature", i);
        put_msg_with_ttl(node->clone, <address from airdrop>, <address size>, key, 12, body, body_size, 10);
        printf("Sending value %s to key %s on address : <address>\n", body, key);
		sleep(1);
	}
}

void send_modulable_message(Node *node){
    char temp;
    char choice[10] = {}, address[100] ={}, key[100] ={};
    scanf("%c", &temp);                                  //Clear buffer
    while(strncmp(choice, "a", 1) != 0 && strncmp(choice, "d", 1) != 0){
       printf("Do you want to add (a) or delete (d) ?\n");
       fgets(choice, sizeof(choice), stdin);

    }
    printf("Type the address you want to interact with :\n");
    fgets(address, sizeof(address), stdin);
    strtok(address, "\n");
    printf("Type the key of you choice :\n");
    fgets(key, sizeof(key), stdin);
    strtok(key, "\n");

    if(strncmp(choice, "a", 1) == 0){
        char msg[100];
        printf("Type the message of you choice :\n");
        fgets(msg, sizeof(msg), stdin);
        strtok(msg, "\n");
        put_msg_default(node->clone, address, strlen(address), key, strlen(key), msg, strlen(msg));
        printf("Sending value %s to key %s on address : %s\n", msg, key, address);
    }
    if(strncmp(choice, "d", 1) == 0){
        remove_msg(node->clone, address, strlen(address), key, strlen(key));
        printf("Deleting key %s on address : %s\n", key, address);
    }
}