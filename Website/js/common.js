/* Common Javascript code for each webpage */

// General Info
var today = new Date();
var year = today.getFullYear();

// Code for showing David's birthday on his log page
var davidBirthdate = new Date('April 6, 1993 00:00:00');
var davidAge = today.getTime() - davidBirthdate.getTime();
davidAge = Math.floor(davidAge / 31556900000)
var element = document.getElementById('david_age');
element.innerHTML = '<p>My age is: ' + davidAge + ' years </p>';

// Updates the footer with the current year
var footer = document.getElementsByTagName("footer");
footer[0].innerHTML = '<p>Copyright &copy ' + year + ' ESE Team</p>';