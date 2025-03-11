document.addEventListener('DOMContentLoaded', function() {
    document.querySelectorAll('.section').forEach(question => {
        question.addEventListener('click', function(event) {
            if (event.target.matches('.option')) {
                let questionId = event.target.getAttribute('question');
                document.querySelectorAll(`.option[question="${questionId}"]`)
                    .forEach(questionButton => questionButton.classList.remove('clicked_button'));
                event.target.classList.add('clicked_button');
            }
            else if (event.target.matches('#submit_answer')) {
                document.querySelectorAll('.option').forEach(answer => {
                    let answerId = answer.getAttribute('question');
                    if (!answerId) return;
                    document.querySelectorAll(`.option[question="${answerId}"]`).forEach(questionAnswer => {
                        if (questionAnswer.classList.contains('clicked_button')) {
                            let checkAnswer = document.querySelector(`.check_answer[question="${answerId}"]`);
                            if (!checkAnswer) return;
                            checkAnswer.style.visibility = 'visible';
                            if (questionAnswer.id == `answer_${answerId}`) {
                                checkAnswer.style.backgroundColor = '#90ff93';
                                checkAnswer.innerHTML = 'Correct!';
                            }
                            else {
                                checkAnswer.style.backgroundColor = '#ffc8c8';
                                checkAnswer.innerHTML = 'Incorrect';
                            }
                        }
                    });
                });

                document.querySelectorAll('.free_response').forEach(answer => {
                    let answerId = answer.getAttribute('question');
                    if (!answerId) return;
                    let textInput = document.querySelector(`.response_answer[question="${answerId}"]`);
                    if (!textInput) return;
                    let checkAnswer = document.querySelector(`.check_answer[question="${answerId}"]`);
                    if (!checkAnswer) return;
                    checkAnswer.style.visibility = 'visible';
                    let textAnswer = document.querySelector(`.response_answer[question="${answerId}"]`).getAttribute('answer');
                    if (!textInput.value.trim()) {
                        checkAnswer.style.backgroundColor = '#ffc8c8';
                        checkAnswer.innerHTML = 'No answer';
                    }
                    else if (textInput.value.trim().toLowerCase() == textAnswer) {
                        checkAnswer.style.backgroundColor = '#90ff93';
                        checkAnswer.innerHTML = 'Correct!';
                    }
                    else {
                        checkAnswer.style.backgroundColor = '#ffc8c8';
                        checkAnswer.innerHTML = 'Incorrect';
                    }
                });
            }
        });
    });
});