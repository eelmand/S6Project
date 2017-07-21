// https://stackoverflow.com/questions/5835126/javascript-infinite-loop

var json_data = {};
var users = document.getElementById('users');

window.onload = function start(){
    // Get user info as JSON from the new_users table
    $.ajax({
        url: 'http://adequateelevators.com/Website/php/get_new_users.php',
        dataType: 'json',
        success: function(data) {
            json_data = data;
            console.log(json_data);

            for (var i in json_data) {
              var table = document.getElementById("users");
              var tr = document.createElement("tr");
              var username = document.createElement("td");
              var first_name = document.createElement("td");
              var last_name = document.createElement("td");
              
              username.appendChild(document.createTextNode(json_data[i].username));
              tr.appendChild(username);
              first_name.appendChild(document.createTextNode(json_data[i].first_name));
              tr.appendChild(first_name);
              last_name.appendChild(document.createTextNode(json_data[i].last_name));
              tr.appendChild(last_name);
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