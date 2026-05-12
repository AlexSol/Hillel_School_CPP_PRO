#!/bin/bash
# WSL Qt Quick launcher helper
# Спеціально для запуску Qt Quick додатків у WSL

export QT_QPA_PLATFORM=offscreen
export QT_LOGGING_RULES="qt.qpa.*=false"

# Перевіримо наявність X11 сервера
if command -v Xvfb &> /dev/null; then
    # Якщо є Xvfb, використаємо його (віртуальний дисплей)
    Xvfb :99 -screen 0 1024x768x24 > /dev/null 2>&1 &
    XVFB_PID=$!
    export DISPLAY=:99
    sleep 1
elif [ -n "$DISPLAY" ]; then
    # Якщо DISPLAY вже встановлен, використаємо його
    echo "Using existing DISPLAY=$DISPLAY"
else
    # В іншому випадку намагаємось запустити з offscreen
    echo "Running with QT_QPA_PLATFORM=offscreen"
    export QT_QPA_PLATFORM=offscreen
fi

# Запускаємо програму
"$@"
EXIT_CODE=$?

# Прибираємо Xvfb якщо його запускали
if [ -n "$XVFB_PID" ]; then
    kill $XVFB_PID 2>/dev/null
fi

exit $EXIT_CODE
