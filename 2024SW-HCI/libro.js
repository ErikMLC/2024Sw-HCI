document.addEventListener("DOMContentLoaded", function () {
    const params = new URLSearchParams(window.location.search);

    // Función para decodificar y asignar valores
    function setTextContent(id, value) {
        document.getElementById(id).textContent = value || 'N/A';
    }

    // Asignar los valores a los elementos correspondientes
    setTextContent('titulo-obra', params.get('titulo'));
    setTextContent('autor', params.get('autor'));
    setTextContent('editorial', params.get('editorial'));
    setTextContent('tipoObra', params.get('tipoObra'));
    setTextContent('fechaPublicacion', params.get('fechaPublicacion'));
    setTextContent('genero', params.get('genero'));
    setTextContent('estado', params.get('estado'));
});
