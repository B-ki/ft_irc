#ifndef CHANNEL_HPP
#define CHANNEL_HPP 

# include <vector>
# include <stdlib.h>
# include <ctime>
# include "server/Client.h"
# include "command/reply_command.h"
# include "command/error_command.h"
# include "error.h"
# include "utils.h"

class Channel
{
	public:
		// -- Public Constructors --
		Channel(Client* user, const std::string& name);
		Channel(const Channel& other);
		~Channel();
		Channel& operator=(const Channel& other);

		// -- Getters --
		const std::string&                get_name() const;
		const std::vector<const Client*>& get_admins() const;
		const std::vector<const Client*>& get_members() const;
		bool                              is_invite_only() const;
		bool                              is_topic_restricted() const;
		bool                              is_password_restricted() const;
		const std::string&                get_password() const;
		const std::string&                get_topic() const;
		const std::string&                get_topic_setter_nick() const;
		const std::string&                get_topic_set_time() const;
		int                               get_max_users() const;

		// -- Setters
		void    set_invite_only(bool invite_only);
		void    set_topic_restriction(bool topic_restriction);
		void    set_password_activation(bool password_activation);
		void    set_password(const std::string& password);
		void    set_topic(const Client& user, const std::string& topic);
		void 	set_max_users(size_t max_users);

		// -- Public Functions --
		void    add_user(Client* user);
		void    part_user(Client* user, const std::string& reason);
		void	kick_user(Client*user, Client* target, const std::string& reason);
		void    quit_user(Client* user, const std::string& reason);
		void    add_admin(const Client* user);
		void    remove_admin(const Client* user);
		bool    is_admin(const Client* user) const;
		bool    is_full() const;
		bool    is_invited(const Client* user) const;
		bool    is_in_channel(const Client* user) const;
		bool    validate_password(const std::string& password) const;
		void    invite_user(const Client* user, const Client* target);
		bool    is_empty() const;

		std::string get_mode_list() const;


		void    send_message(const Client* user, const std::string& message);
		void    send_all(const Client* user, const std::string& message);


	private:
		// -- Private Variables --
		std::string 			            _name;
		std::vector<const Client*>          _admins;
		std::vector<const Client*>          _members;
		std::vector<const Client*>          _invited;
		bool                                _invite_only;
		bool                                _topic_restriction;
		bool                                _password_restriction;
		std::string                         _password;
		std::string                         _topic;
		size_t                              _max_users;
		bool                                _capacity_restriction;
		std::pair<std::string, std::string> _topic_info;

		// -- Private Functions --
		std::vector<const Client*>::const_iterator  find_user(const std::vector<const Client*>& list, const Client* elem) const;
		std::vector<const Client*>::iterator        find_user(std::vector<const Client*>& list, const Client* elem);
		std::string                                 get_nicks_list() const;
		void                                        remove_user(Client* user);
};

#endif
