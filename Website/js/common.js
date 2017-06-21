/* Common Javascript code for each webpage */

var today = new Date();
var year = today.getFullYear();

// Updates the footer with the current year
var footer = document.getElementsByTagName("footer");
footer[0].innerHTML = '<p>Copyright &copy ' + year + ' ESE Team</p>';