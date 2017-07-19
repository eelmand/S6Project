// Question 26 assignment 1 - ensure user has completed all required fields before submitting form


window.onload = function start() {
	var username = document.getElementById('username');
	var password = document.getElementById('password');
	var first_name = document.getElementById('first_name');
	var last_name = document.getElementById('last_name');
	var student = document.getElementById('student');
	var faculty = document.getElementById('faculty');
	var info = document.getElementById('info_message');

	var form = document.getElementById('submit');

	form.onsubmit = function() {
		if(username.value.length < 7) {
			alert('Username must be at least 7 characters long');
			return false;
		}
		if(password.value.length < 7) {
			alert('Password must be at least 7 characters long');
			return false;
		}
		if(first_name.value.length < 1) {
			alert('Please enter a First Name');
			return false;
		}
		if(last_name.value.length < 1) {
			alert('Please enter a Last Name');
			return false;
		}

		if(!(student.checked || faculty.checked)) {
			alert('Please choose Student or Faculty');
			return false;
		}

		if(info.value.length < 1) {
			alert('Please tell us a bit about yourself');
			return false;
		}
	}
}

// Question 25 Assignment 1 - Character limit on textarea field

function character_count(e){
	var text_entered, char_display, counter;
	text_entered = document.getElementById('info_message').value;
	char_display = document.getElementById('characters_remaining');

	counter = (180 - (text_entered.length));
	char_display.innerHTML = "Characters remaining: " + counter;

	if(counter <= 0){
		alert('Please do not exceed 180 characters');
	}
}

var element = document.getElementById('info_message');
element.addEventListener('keyup', character_count, false);
