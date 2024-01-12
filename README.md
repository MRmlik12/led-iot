# LED WiFi

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![TypeScript](https://img.shields.io/badge/typescript-%23007ACC.svg?style=for-the-badge&logo=typescript&logoColor=white)
![Espressif](https://img.shields.io/badge/espressif-E7352C.svg?style=for-the-badge&logo=espressif&logoColor=white)
![Vite](https://img.shields.io/badge/vite-%23646CFF.svg?style=for-the-badge&logo=vite&logoColor=white)


Control your LEDs with any your device

## Build and deploy

### Tools needed
* PlatformIO>=6.1.13
* Node.js>=20.10 with pnpm>=8.12.0

### Edit Configuration
```json
// iot/data/config.json
{
  "ssid": "WiFi SSID", // WiFi SSID 
  "password": "", // WiFi password
  "hostname": "" // Example hostname to manage your LEDs ex. your-domain.local
}
```

### Build project

```sh
$ ./scripts/setup.sh
$ ./scripts/build-frontend.sh
$ ./scripts/build-firmware.sh
```

### Clean

```sh
$ ./scripts/clean.sh
```

## After deploy
1. Open your browser
2. Type your hostname to web browser
3. Done :)