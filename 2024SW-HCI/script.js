document.addEventListener("DOMContentLoaded", function () {
    const searchButton = document.getElementById('search-button');
    const searchInput = document.getElementById('search-input');

    Papa.parse("biblioteca.csv", {
        download: true,
        header: true,
        complete: function (results) {
            const data = results.data;

            // Rellenar la tabla como antes
            const tableBody = document.getElementById('biblioteca-table-body');
            if(tableBody) {
                data.forEach(row => {
                    if (row.Titulo && row.Autor && row.Estado) {
                        const tr = document.createElement('tr');
                        const columns = ['Titulo', 'Autor', 'Estado'];

                        columns.forEach(col => {
                            const td = document.createElement('td');

                            if (col === 'Titulo') {
                                const a = document.createElement('a');
                                a.textContent = row[col];

                                const params = new URLSearchParams({
                                    titulo: row['Titulo'],
                                    autor: row['Autor'],
                                    editorial: row['Editorial'],
                                    tipoObra: row['Tipo de Obra'],
                                    tipoAutor: row['Tipo de Autor'],
                                    fechaPublicacion: row['Fecha de Publicacion'],
                                    genero: row['Genero'],
                                    estado: row['Estado'],
                                    codigoOrcid: row['Link']
                                });

                                a.href = `libro.html?${params.toString()}`;
                                td.appendChild(a);
                            } else if (col === 'Autor') {
                                const a = document.createElement('a');
                                a.textContent = row[col];

                                const params = new URLSearchParams({
                                    nombreAutor: row['Autor'],
                                    tipoAutor: row['Tipo de Autor'],
                                    codigoOrcid: row['Link']
                                });

                                a.href = `autor.html?${params.toString()}`;
                                td.appendChild(a);
                            } else {
                                td.textContent = row[col] ? row[col] : '';
                            }
                            tr.appendChild(td);
                        });

                        tableBody.appendChild(tr);
                    }
                });
            }

            // Funcionalidad de búsqueda
            searchButton.addEventListener('click', () => {
                const searchTerm = searchInput.value.trim().toLowerCase();
                const foundRow = data.find(row =>
                    row.Titulo.toLowerCase() === searchTerm || row.Autor.toLowerCase() === searchTerm
                );

                if (foundRow) {
                    if (foundRow.Titulo.toLowerCase() === searchTerm) {
                        // Redirigir a libro.html
                        const params = new URLSearchParams({
                            titulo: foundRow['Titulo'],
                            autor: foundRow['Autor'],
                            editorial: foundRow['Editorial'],
                            tipoObra: foundRow['Tipo de Obra'],
                            tipoAutor: foundRow['Tipo de Autor'],
                            fechaPublicacion: foundRow['Fecha de Publicacion'],
                            genero: foundRow['Genero'],
                            estado: foundRow['Estado'],
                            codigoOrcid: foundRow['Link']
                        });
                        window.location.href = `libro.html?${params.toString()}`;
                    } else if (foundRow.Autor.toLowerCase() === searchTerm) {
                        // Redirigir a autor.html
                        const params = new URLSearchParams({
                            nombreAutor: foundRow['Autor'],
                            tipoAutor: foundRow['Tipo de Autor'],
                            codigoOrcid: foundRow['Link']
                        });
                        window.location.href = `autor.html?${params.toString()}`;
                    }
                } else {
                    alert('No se encontró ningún libro o autor con ese nombre.');
                }
            });
        },
        error: function (error) {
            console.error("Error al procesar el CSV:", error);
        }
    });
});
