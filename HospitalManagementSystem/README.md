# Hospital Management System (C)

A console-based Hospital Management System written in C. It manages patients,
doctors, appointments and billing, storing all data in plain text files.

## Features

- Admin login with masked password entry
- **Patients** - add, view, search, update, delete
- **Doctors** - add, view, search, update, delete
- **Appointments** - add, view, search, update, delete
- **Billing** - generate, view, search, update, delete
- Input validation (ID, name, age, gender, phone, blood group, date, time, status, amounts)

## Project Structure

```
HospitalManagementSystem/
├── include/
│   ├── appointment.h
│   ├── billing.h
│   ├── doctor.h
│   ├── patient.h
│   ├── ui.h
│   └── validation.h
├── src/
│   ├── appointment.c
│   ├── billing.c
│   ├── doctor.c
│   ├── main.c          (login, dashboard, program flow)
│   ├── patient.c
│   ├── ui.c            (header/success/error messages, password input)
│   └── validation.c
├── Makefile
├── README.md
└── .gitignore
```

## Build

With `make`:

```
make
```

Or directly with GCC:

```
gcc -Wall -Wextra -std=c99 -Iinclude src/*.c -o hospital
```

On Windows (MinGW), use `gcc ... -o hospital.exe` (or `mingw32-make`).

## Run

```
./hospital          # Windows: hospital.exe
```

Default credentials: `admin` / `1234`

Data is stored in `patients.txt`, `doctors.txt`, `appointments.txt` and
`bills.txt`, created in the directory you run the program from.

## Notes

- Password input uses `<conio.h>` on Windows and a `termios` fallback on
  Linux/macOS, so the project builds on all three.
- Records are stored as space-separated text, so fields such as names cannot
  contain spaces.
