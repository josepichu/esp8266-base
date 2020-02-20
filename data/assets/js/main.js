$(document).ready(function() {

    console.log('JQuery ready ...');

    $("#switch-1").on('change', function(e) {

        console.log($(this).is(":checked"));

        // $.post('LEFD')


    });


    function actualizar() {

        $.get("getData", function(response) {
            $("#sensor_info").html(response.data + "%")
            $("#log").append(JSON.stringify(response));

            if (response.data > 70) {
                $("#sensor_info").removeClass('orange');
                $("#sensor_info").removeClass('red');
                $("#sensor_info").addClass('green')

            } else if (response.data < 30) {
                $("#sensor_info").removeClass('orange');
                $("#sensor_info").removeClass('green');
                $("#sensor_info").addClass('red')
            } else {
                $("#sensor_info").removeClass('red');
                $("#sensor_info").removeClass('green');
                $("#sensor_info").addClass('orange')
            }

        });

    }

    $("#actualizar").on('click', actualizar)

    // init nivel
    actualizar();

});