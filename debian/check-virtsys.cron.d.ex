#
# Regular cron jobs for the check-virtsys package
#
0 4	* * *	root	[ -x /usr/bin/check-virtsys_maintenance ] && /usr/bin/check-virtsys_maintenance
