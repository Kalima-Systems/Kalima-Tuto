#ifndef FILEWATCHER_H
#define FILEWATCHER_H

/**
 * @file filewatcher.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief Will watch a directory and wait for event notify
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../KalimaCUtil/BytesArray.h"

/**
 * @brief If event notified isn't usefull
 * 
 */
#define EVENT_NONE 0
/**
 * @brief If a new file is created
 * 
 */
#define EVENT_CREATE 1
/**
 * @brief If a file is modified
 * 
 */
#define EVENT_MODIFY 2
/**
 * @brief If a file is moved
 * 
 */
#define EVENT_MOVE 3
/**
 * @brief If a file is deleted
 * 
 */
#define EVENT_DELETE 4

/**
 * @brief Get event's file's name
 * 
 * @param fd Inotify instance
 * @param event_name File's name
 * @return Type of event (see defines) 
 */
int get_event (int fd, char** event_name);

/**
 * @brief Initialize a inotify event and return instance
 * 
 * @return Inotify's instance
 */
int init_filewatcher();

//Ajoute un fichier ou un dossier à l'instance inotify, retourne un watch descriptor

/**
 * @brief Add inotify instance watching a directory
 * 
 * @param fd Inotify instance
 * @param path Directory to watch path
 */
void init_add_watch(int fd,char* path);

#endif