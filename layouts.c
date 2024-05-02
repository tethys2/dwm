void
fibonacci(Monitor *m) {
	unsigned int i, n, mh,h, w, x, y, mw, my;
	// mh is the master height mw is master my is accumulated master height width h is tile height w is tile width x is tile x y is tile y  
	Client *c;

	//gets n which is the number of window on the screen
	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;
	//if there is clients in the stack
	if (n > m->nmaster)
		//if there are masters then set the master width to the workspace width times the ratio otherwise zero
		mw = m->nmaster ? m->ww * m->mfact : 0;
	else
		//master width is the whole workspace
		mw = m->ww - m->gappx;
	//move the top right corner of stack to where it should be
	x = mw + m ->gappx;
	y = m ->gappx;
	h = (m ->wh) - 2 * (m ->gappx);
	w = (m ->ww) - mw - 2* (m ->gappx) ;  
	//loop through all of the windows
	for (i = 0, my = m->gappx, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
		// if a master window
		if (i < m->nmaster) {
			mh = (m->wh - my) / (MIN(n, m->nmaster) - i) - m->gappx;
			resize(c, m->wx + m->gappx, m->wy + my, mw - (2*c->bw) - m->gappx, mh - (2*c->bw), 0);
			
			if (my + HEIGHT(c) + m->gappx < m->wh)
				my += HEIGHT(c) + m->gappx;
		}
		else{
			//make sure this is not the last window
			if(i < n -1){
				//switch between 4 different kinds of splits repeating after the masters
				//each split decreases the size and then moves the next window top corner
				//this makes handling the last window really easy
				switch((i - m->nmaster) % 4){
					case 0:
						h /= 2;
						if(h > (m->gappx/2))
							h -= (m->gappx)/2;
						resize(c, m->wx + x, m->wy + y, w - (2*c->bw), h - (2*c->bw), 0);
						y += h + m->gappx;
						break;
					case 1:	
						w /= 2;
						if(w > (m ->gappx)/2)
							w -= (m ->gappx)/2;
						resize(c, m->wx + x + w + m->gappx, m->wy + y, w - (2*c->bw), h - (2*c->bw), 0);
						break;
					case 2:
						h /= 2;
						if(h > (m->gappx/2))
							h -= (m->gappx)/2;
						resize(c, m->wx + x, m->wy + y + h + (m->gappx), w - (2*c->bw), h - (2*c->bw), 0);

						break;
					case 3:
						w /= 2;
						if(w > (m ->gappx)/2)
							w -= (m ->gappx)/2;
						resize(c, m->wx + x, m->wy + y, w - (2*c->bw), h - (2*c->bw), 0);
						x += w + (m ->gappx);
						break;
				}
			}
			else{
				//this will cause the window to use the rest of the space and not make another spit
				resize(c, m->wx + x, m->wy + y, w - (2*c->bw), h - (2*c->bw), 0);
			}
		}
}

void
mtile(Monitor *m)
{
	unsigned int i, n, whenover, overh, tmp, x, y, w, h, mh, mw, my;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;

	if (n > m->nmaster){
		mw = m->nmaster ? m->ww * m->mfact : 0;

		x = mw + m ->gappx;
		y = m ->gappx;
		// calculates the regular height then divides by the number of windows in each column
		h = ((m ->wh) - 2 * (m ->gappx)) / ((n- (m->nmaster)) / (m->ntile));
		if (h - (tmp = (m->gappx) * ((n- (m->nmaster)) / (m->ntile))) > 0)
			h -= tmp;
		//if there is extra
		if((n - m->nmaster) % (m ->ntile)){ 
			overh = ((m ->wh) - 2 * (m ->gappx)) / ((n- (m->nmaster)) / (m->ntile) + 1);
			if (overh - (tmp = ((m->gappx) * ((n- (m->nmaster)) / (m->ntile) + 1))) > 0)
				overh -= tmp;
		}
		// calculates the regular width then divides by the number of tiles and subtracts ntile many gaps
		w = ((m ->ww) - mw - 2* (m ->gappx)) / (m->ntile) - (m ->ntile) * (m->gappx); 
		if (w - (tmp = ((m->gappx) * (m->ntile))) > 0)
				w -= tmp;
		//number of columes without extra times the number in each tile with extra
		whenover = ((m->ntile) - (m->ntile) % n) * ((n- (m->nmaster)) / (m->ntile));
	}
	else
		mw = m->ww - m->gappx;
	for (i = 0, my = m->gappx, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
		if (i < m->nmaster) {
			mh = (m->wh - my) / (MIN(n, m->nmaster) - i) - m->gappx;
			resize(c, m->wx + m->gappx, m->wy + my, mw - (2*c->bw) - m->gappx, mh - (2*c->bw), 0);
			if (my + HEIGHT(c) + m->gappx < m->wh)
				my += HEIGHT(c) + m->gappx;
		} else {
			resize(c, m->wx + x, m->wy + y, w - (2*c->bw), h - (2*c->bw), 0);
		}
}



