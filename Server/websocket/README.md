# WebSocket

Websocket is used to send events and update some informations on pages without
having to refresh it (notifications, chat, login/logout data, ...).

### ROUTE => ws://localhost:8081/ws/:token


```
When a user logins he receives :
- His notif list
- His match list

It also updates his last_activity status and sends the login event to
every other connected users.

When a user logouts it sends a logout event to every other connected users.
```


### EVENTS

**LIKE** :
- Sends a profile liked by 'foo' notification

**UNLIKE** :
- Sends a profile unliked by 'foo' notification
- Sends an updated match list to both users

**MATCH** :
- Sends a profile matched with 'foo' notification
- Sends an updated match list to both users

**VISIT** :
- Sends a profile visited by 'foo' notifiction

**MESSAGE** :
- Adds message to Database
- Sends a received a message from 'foo' notification
- Sends the message to user_target

**VIEWED** :
- Sets the notif_id list as viewed in Database

**IS_TYPING** :
- Sends an is_typing event to user_target with boolean value

**LOGOUT** :
- Sends a logout event to everyone else that is online
