// Question 26 assignment 1 - ensure user has completed all required fields before submitting form


window.onload = function start() {
	var first_name = document.getElementById('first_name');
	var last_name = document.getElementById('last_name');
	var student = document.getElementById('student');
	var faculty = document.getElementById('faculty');
	var info = document.getElementById('info');

	var form = document.getElementById('login');

	form.onsubmit = function() {
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