// https://stackoverflow.com/questions/5835126/javascript-infinite-loop

var users_data = {};
var new_users_data = {};
var users = document.getElementById('users');
var new_users = document.getElementById('new_users');

window.onload = function start(){
    // Get new users info as JSON from the new_users table
    $.ajax({
        url: 'http://adequateelevators.com/Website/php/get_new_users.php',
        dataType: 'json',
        success: function(data) {
            new_users_data = data;
            console.log(new_users_data);

            for (var i in new_users_data) {
              var table = document.getElementById("new_users");
              var tr = document.createElement("tr");
              var username = document.createElement("td");
              var first_name = document.createElement("td");
              var last_name = document.createElement("td");
              var email = document.createElement("td");
              var last_login = document.createElement("td");
              
              username.appendChild(document.createTextNode(new_users_data[i].username));
              tr.appendChild(username);
              
              first_name.appendChild(document.createTextNode(new_users_data[i].first_name));
              tr.appendChild(first_name);
              
              last_name.appendChild(document.createTextNode(new_users_data[i].last_name));
              tr.appendChild(last_name);
              
              email.appendChild(document.createTextNode(new_users_data[i].email));
              tr.appendChild(email);

              last_login.appendChild(document.createTextNode(new_users_data[i].last_login));
              tr.appendChild(last_login);

              table.appendChild(tr);
            }
        }
    });

    // Get users info as JSON from the users table
    $.ajax({
        url: 'http://adequateelevators.com/Website/php/get_users.php',
        dataType: 'json',
        success: function(data) {
            users_data = data;
            console.log(users_data);

            for (var i in users_data) {
              var table = document.getElementById("users");
              var tr = document.createElement("tr");
              var username = document.createElement("td");
              var first_name = document.createElement("td");
              var last_name = document.createElement("td");
              var email = document.createElement("td");
              var last_login = document.createElement("td");
              
              username.appendChild(document.createTextNode(users_data[i].username));
              tr.appendChild(username);
              
              first_name.appendChild(document.createTextNode(users_data[i].first_name));
              tr.appendChild(first_name);
              
              last_name.appendChild(document.createTextNode(users_data[i].last_name));
              tr.appendChild(last_name);
              
              email.appendChild(document.createTextNode(users_data[i].email));
              tr.appendChild(email);

              last_login.appendChild(document.createTextNode(users_data[i].last_login));
              tr.appendChild(last_login);

              table.appendChild(tr);
            }
        }
    });

    // Monitor the grant access form
    var form = document.getElementById('login');

    form.onsubmit = function() {
        if(username.value.length < 7) {
            alert('Username must be at least 7 characters long');
            return false;
        }
    }
}