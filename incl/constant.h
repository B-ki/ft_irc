#ifndef CONSTANT_H
# define CONSTANT_H

# define BUFFER_SIZE 1024

typedef enum 
{
	UNKNOWN = 0,
	CAP,
	PASS,
	NICK,
	USER,
	JOIN,
	PART,
	PRIVMSG,
	QUIT,
	KICK,
	INVITE,
	NOTICE,
	TOPIC,
	MODE
} cmd_type;

#endif
