service Echo {
    string echo(1:string msg);
	void send(1:string msg);
	void oneway_send(1:string msg);
}
