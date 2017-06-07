<?php
echo '
	<div class="container">
		<div class="navbar-header">
			<button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#myNavbar">
				<span class="icon-bar"></span>
				<span class="icon-bar"></span>
				<span class="icon-bar"></span>                        
			</button>
			<a class="navbar-brand" href="index.html">S6 Project</a>
		</div>
		
		<div class="collapse navbar-collapse" id="myNavbar">
			<ul class="nav navbar-nav">
				<li><a href="about.html">About</a></li>
				<li><a href="phase_1.html">Phase 1</a></li>
				<li><a href="phase_2.html">Phase 2</a></li>
				<li><a href="phase_3.html">Phase 3</a></li>
				<li class="dropdown">
					<a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-haspopup="true" aria-expanded="false">Logbooks <span class="caret"></span></a>
					<ul class="dropdown-menu">
						<li><a href="stan_rashevskyi_log_book.html">Stan Rashevskyi</a></li>
						<li><a href="david_eelman_log_book.html">David Eelman</a></li>
						<li><a href="thomas_abdallah_log_book.html">Thomas Abdallah</a></li>
					</ul>
				</li>
				<li><a href="dashboard.html">Dashboard</a></li>
			</ul>
			<ul class="nav navbar-nav navbar-right">
				<li><a href="login.html"><span class="glyphicon glyphicon-log-in"></span> Login</a></li>
			</ul>
		</div>
	</div>
';
?>

