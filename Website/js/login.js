// Event listener to ensure that username and password are both at least 7 characters long
//focus username text input when page has loaded

window.onload = function start() {
	var username = document.getElementById('username');
	var password = document.getElementById('password');
	var form = document.getElementById('login');

	form.onsubmit = function() {
		if(username.value.length < 7) {
			alert('Username must be at least 7 characters long');
			return false;
		}
		if(password.value.length < 7) {
			alert('Password must be at least 7 characters long');
			return false;
		}
	}
}


function focus_username() {
	var user_input = document.getElementById('username');
	user_input.focus();
}

window.addEventListener('load', focus_username, false);