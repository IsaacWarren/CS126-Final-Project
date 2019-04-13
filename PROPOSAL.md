    My final project proposal is a pong game that can operate in several modes. The first mode is typical two player pong where both paddles are controlled by human players. In training mode two paddles controlled by randomly generated neural networks compete, the winner produces two offspring with mutated weights and the loser dies. This can continue for many generations. The final mode is one human player playing against a trained AI.

    The pong game section shouldn't take too long. I've developed basic games in a python library called pygame before. The graphics functions seem fairly similar so I think I have a decent idea what I'm doing in this regard.

    The neural network stuff is where I plan on spending most of my time. I have a minimal nerual network library called FANN installed and compiling with openframeworks.

    In terms of timeline I want to get pong done the first week, neural network stuff the second and bugfixes/glueing it all togethor the third.

    Possible extensions:
    clients and servers for remote playing