document.getElementById('formulario-grabovoi').addEventListener('submit', function(event) {
    event.preventDefault();

    const secuencia = document.getElementById('secuencia-numerica').value;
    document.querySelector('.formulario-meditacion').style.display = 'none';
    document.getElementById('pantalla-meditacion').style.display = 'block';

    repetirSecuencia(secuencia, 3 * 60); // 3 minutos en total
});

function repetirSecuencia(secuencia, duracionTotal) {
    const numeros = secuencia.split('');
    let indice = 0;
    let tiempoTranscurrido = 0;
    let mostrarNumero = true;

    const intervalo = setInterval(() => {
        if (tiempoTranscurrido >= duracionTotal) {
            clearInterval(intervalo);
            // Lógica al finalizar
        } else {
            if (mostrarNumero) {
                mostrarNumeroFuncion(numeros[indice]);
                indice = (indice + 1) % numeros.length;
                if (indice === 0) {
                    mostrarNumero = false;
                    setTimeout(() => mostrarNumero = true, 3000); // Pausa de 3 segundos
                }
            } else {
                document.getElementById('numero-en-esfera').textContent = '';
            }
        }
        tiempoTranscurrido++;
    }, 1000); // Cada "tick" es de 1 segundo
}

function mostrarNumeroFuncion(num) {
    const elementoNumero = document.getElementById('numero-en-esfera');
    elementoNumero.classList.remove('animated');
    
    // Forzar el reflujo del DOM. Esta es la parte clave.
    void elementoNumero.offsetWidth;

    elementoNumero.classList.add('animated');
    elementoNumero.textContent = num;
}

