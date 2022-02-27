#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "../lib_KalimaMQC/nodelib/Node.h"

char pre_config[] = "config.txt";

void Menu();
void send_default_message(Node *node);
void send_modulable_message(Node *node);

int main(int argc, char* argv[]) {
    int retry = 0, choice = 0;
    Node *node;
    if(argc>1){
        node = create_Node(argv[1]);
        printf("%s Loaded\n", argv[1]);
    }
    else{
        node = create_Node(pre_config);
        printf("%s Loaded\n", pre_config);
    }
    printf("GO!\n");
    Menu();
    while(retry == 0){
        scanf("%d", &choice);
        if ( choice == 1) {
            send_default_message(node);
            retry = 1;
        } else if (choice == 2) {
            send_modulable_message(node);
            retry = 1;
        }
    }
}

void Menu() {
  printf( "commands available :\n" );
  printf( "- 1 ==> Send a message with default settings\n" );
  printf( "- 2 ==> Send a modulable message\n" );
}

//Default Message is : cache path = /sensors, key = key, ttl(time to live) = -1
void send_default_message(Node *node) {
    char str[100];
    char temp;
    printf("Message to send to Blockchain :\n");
    scanf("%c", &temp);                                 //Clear buffer
    fgets(str, sizeof(str), stdin);                     //Get input
    send_Message_to_Notaries(node, str);                //Send message
    printf("Message sent\n");
    sleep(2);                                           //Waiting for response (in logs)
}

void send_modulable_message(Node *node) {
    proplist kProps = Initiate_prop_List();
    kProps = set_prop(kProps, "ttl", 3, "-1", 2); // will give ttl=-1, meaning the message will stay in blockchain (ttl = time to live)
    char type = encode_Type(PUB); //Publish
    char cachePath[100], key[100], msg[100];
    char temp;
    printf("Type the cachePath you want to interact with :\n");
    scanf("%c", &temp);                                  //Clear buffer
    fgets(cachePath, sizeof(cachePath), stdin);
    strtok(cachePath, "\n");
    printf("Type the key of you choice :\n");
    fgets(key, sizeof(key), stdin);
    strtok(key, "\n");
    printf("Type the message of you choice :\n");
    fgets(msg, sizeof(msg), stdin);
    strtok(msg, "\n");
    KMsg *kmsg = getMessage(node->devid, UUID_SIZE, type, cachePath, strlen(cachePath), key, strlen(key), 1, msg, strlen(msg), kProps);  //Create message
    send_to_Notary_Nodes(node, kmsg->Kmessage);  //Send message
    printf("Message sent\n");
    sleep(2);                                    //Waiting for response (in logs)
}