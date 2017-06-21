// Event listener to ensure that username and password are both at least 7 characters long


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