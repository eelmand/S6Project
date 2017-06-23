/* Common Javascript code for each webpage */

// General Info
var today = new Date();
var year = today.getFullYear();

// Code for showing David's birthday on his log page
var davidBirthdate = new Date('April 6, 1993 00:00:00');
var davidAge = today.getTime() - davidBirthdate.getTime();
davidAge = Math.floor(davidAge / 31556900000);
var element = document.getElementById('david_age');
if(element) {
	element.innerHTML = '<p>My age is: ' + davidAge + ' years </p>';
}

// Code for showing Thomas' birthday on his log page
var thomasBirthdate = new Date('September 14, 1992 00:00:00');
var thomasAge = today.getTime() - thomasBirthdate.getTime();
thomasAge = Math.floor(thomasAge / 31556900000);
var element = document.getElementById('thomas_age');
if(element) {
	element.innerHTML = '<p>My age is: ' + thomasAge + ' years </p>';
}

// Code for showing Stan' birthday on his log page
var stanBirthdate = new Date('October 3, 1996 00:00:00');
var stanAge = today.getTime() - stanBirthdate.getTime();
stanAge = Math.floor(stanAge / 31556900000);
var element = document.getElementById('stan_age');
if(element) {
	element.innerHTML = '<p>My age is: ' + stanAge + ' years </p>';
}

// Updates the footer with the current year
var footer = document.getElementsByTagName("footer");
footer[0].innerHTML = '<p>Copyright &copy ' + year + ' ESE Team</p>';