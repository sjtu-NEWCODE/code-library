void add(int x, int &last) {
	int lastnode = last;
	if (c[lastnode][x]) {
		int nownode = c[lastnode][x];
		if (l[nownode] == l[lastnode] + 1) last = nownode;
		else{
			int auxnode = ++size; l[auxnode] = l[lastnode] + 1;
			for (int i = 0; i < 26; i++) c[auxnode][i] = c[nownode][i];
			f[auxnode] = f[nownode]; f[nownode] = auxnode;
			for (; lastnode && c[lastnode][x] == nownode; lastnode = f[lastnode]) {
				c[lastnode][x] = auxnode;
			}
			last = auxnode;
		}
	} else { // Naive Suffix Automaton
		int newnode = ++size; l[newnode] = l[lastnode] + 1;
		for (; lastnode && !c[lastnode][x]; lastnode = f[lastnode]) c[lastnode][x] = newnode;
		if (!lastnode) f[newnode] = 1;
		else{
			int nownode = c[lastnode][x];
			if (l[lastnode] + 1 == l[nownode]) f[newnode] = nownode;
			else{
				int auxnode = ++size; l[auxnode] = l[lastnode] + 1;
				for (int i = 0; i < 26; i++) c[auxnode][i] = c[nownode][i];
				f[auxnode] = f[nownode]; f[nownode] = f[newnode] = auxnode;
				for (; lastnode && c[lastnode][x] == nownode; lastnode = f[lastnode]) {
					c[lastnode][x] = auxnode;
				}
			}
		}
		last = newnode;
	}
}
