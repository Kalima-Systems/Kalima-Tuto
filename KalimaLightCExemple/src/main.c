#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "Node.h"

char pre_config[] = "etc/cfg/config.txt";

void Menu();
void send_default_message(Node *node);
void send_modulable_message(Node *node);

int main(int argc, char *argv[])
{
    int retry = 0, choice = 0;
    Node *node;
    if (argc > 1){
        node = create_Node(argv[1], NULL);
        if(node == NULL){
        printf("Error creating Node. Please verify the config file\n");
        return 0;
    } 
        Connect_to_Notaries(node, NULL);
        printf("%s Loaded\n", argv[1]);
    }
    else{
        node = create_Node(pre_config, NULL);
        if(node == NULL){
            printf("Error creating Node. Please verify the config file\n");
            return 0;
        } 
        Connect_to_Notaries(node, NULL);
        printf("%s Loaded\n", pre_config);
    }
    printf("GO!\n");
    while (retry == 0){
        Menu();
        scanf("%d", &choice);
        if (choice == 1){
            send_default_message(node);
            retry = 0;
        }else if (choice == 2){
            send_modulable_message(node);
            retry = 1;
        }
    }
}

void Menu(){
    printf("commands available :\n");
    printf("- 1 ==> Send a message with default settings\n");
    printf("- 2 ==> Send a modulable message\n");
}

void send_default_message(Node *node){
    char str[100];
    char temp;
    printf("Message to send to Blockchain :\n");
    scanf("%c", &temp);                  // Clear buffer
    fgets(str, sizeof(str), stdin);      // Get input
    List *kProps = new_propList();
    set_prop(kProps, "ttl", 3, "-1", 2); // will give ttl=-1, meaning the message will stay in blockchain (ttl = time to live)
    KMsg *kmsg = getMessage(node->devid, UUID_SIZE, get_encoded_Type("PUB"), <address from airdrop>, <size>, "Default message", 15, 1, str, strlen(str), kProps); // Create message
    send_KMessage(node, kmsg->Kmessage);
    printf("Message sent\n");
    sleep(2); // Waiting for response (in logs)
}

void send_modulable_message(Node *node){
    List *kProps = new_propList();
    set_prop(kProps, "ttl", 3, "-1", 2); // will give ttl=-1, meaning the message will stay in blockchain (ttl = time to live)

    char type = get_encoded_Type("PUB");
    char address[100], key[100], msg[100];
    char temp;
    printf("Type the address you want to interact with :\n");
    scanf("%c", &temp); // Clear buffer
    fgets(address, sizeof(address), stdin);
    strtok(address, "\n");
    printf("Type the key of you choice :\n");
    fgets(key, sizeof(key), stdin);
    strtok(key, "\n");
    printf("Type the message of you choice :\n");
    fgets(msg, sizeof(msg), stdin);
    strtok(msg, "\n");
    KMsg *kmsg = getMessage(node->devid, UUID_SIZE, type, address, strlen(address), key, strlen(key), 1, msg, strlen(msg), kProps); // Create message
    send_KMessage(node, kmsg->Kmessage);                                                                                         // Send message
    printf("Message sent\n");
    sleep(2); // Waiting for response (in logs)
}