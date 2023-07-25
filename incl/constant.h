#ifndef CONSTANT_H
# define CONSTANT_H

# define BUFFER_SIZE 8

typedef enum 
{
	PASS = 0,
	NICK,
	USER,
	JOIN,
	PART,
	LEAVE,
	PRIVMSG,
	QUIT,
	KICK,
	INVITE,
	NOTICE,
	TOPIC,
	MODE,
	NOTHING
} cmd_type;

#endif
