<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![CMake][cmake-shield]][cmake-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]



<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/kiddersmxj/stdstreams">
    <!-- <img src="images/logo.png" alt="Logo" width="80" height="80"> -->
  </a>

<h3 align="center">stdstreams</h3>

  <p align="center">
    Simple tool to redirect std streams into user configured visually appealing outputs
    <br />
    <!-- <a href="https://github.com/github_username/repo_name"><strong>Explore the docs »</strong></a> -->
    <br />
    <br />
    <!-- <a href="https://github.com/github_username/repo_name">View Demo</a> -->
    <!-- · -->
    <a href="https://github.com/github_username/repo_name/issues">Report Bug</a>
    ·
    <a href="https://github.com/github_username/repo_name/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <!-- <li><a href="#contributing">Contributing</a></li> -->
    <li><a href="#license">License</a></li>
    <!-- <li><a href="#contact">Contact</a></li> -->
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

The project aim is to turn the first, messy, hard to read/diagnose output from any program
one may be building/debugging (we've all been there with print messages) into the easy to
read and debug visual output in the second image.

![stdstreams Screen Shot][product-screenshot]

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

* [![CPP][CPP]][CPP-url]
* [![FTXUI][FTXUI]][FTXUI-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>



## Getting Started

### Prerequisites

* CMake
    [https://cmake.org/install](https://cmake.org/install)

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/kiddersmxj/stdstreams
   ```
2. Use CMake via install script
   ```sh
   cd stdstreams && ./install.sh
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

stdstreams can be used with any child program that prints to stdout in the way described in the usage notes at the bottom.

Here is an example of usage with a simple mcu, reading two potentiometers and a button. Marked using P1, P2 and B1:

![stdstreams-mcu-stdout][stdstreams-mcu-stdout]

The command used there was `stdstreams --program="arduino-cli monitor -p /dev/ttyACM0"`

To run the testing (bash) script use `stdstreams -p tests/stdout.sh`

```
usage: stdstreams  [ -o/--options=value ] [ -p/--program=value ]
Make sure to give the full path of the program

options:
    -h / --help         show help and usage notes
    -v / --version      print version and exit
    -p / --program      program to parse stdout

Program can be utilised to parse any program that can or does 
write to stdout. 

Format specified as such:
Mode=Neutral, Speed=41, Potentiometer Position=-29, Status=Throttle
but no drive selected\n,

The use of \n at the end of each line or equivilent endl character
is vital to sucsessful execution. The use of quotes around values 
are not required. Program used the "," comma to delimit its values.
Keeping the order of variables is also nessecary as program uses
indicies to refernece values rather than names.

Errors may occur under the following circumstances in the current 
version (check using -v):
-   The user running the command does not have 
    access to the stdout of the program run. Please check this is not 
    the case.
-   The $ProgramLatency is too high in comparison the the speed of 
    stdout write from the child.
```

<!-- _For more examples, please refer to the [Documentation](https://example.com)_ -->

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ROADMAP -->
## Roadmap

- [x] Program wrapper to run/open stream to be parsed
- [x] TUI
    - [x] Graphing
    - [x] Min, Max, Avg values
    - [x] Status messages to be printed in seperate area
    - [x] Handle int and string variables
    - [ ] Single page/moment iterating
    - [ ] Gauges
- [ ] Init file
    - [ ] Quick run command
    - [ ] Project default settings
    - [ ] Customising of output
        - [ ] Graph vs gauge
        - [ ] Colours for specific variables
        - [ ] Constraning values to colour gradient range
- [ ] gdb interfacing/incorporation

See the [open issues](https://github.com/github_username/repo_name/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* [ftxui - ArthurSonzogni](https://github.com/ArthurSonzogni/FTXUI)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[cmake-shield]: https://img.shields.io/github/actions/workflow/status/kiddersmxj/stdstreams/cmake.yml?style=for-the-badge
[cmake-url]: https://github.com/kiddersmxj/stdstreams/actions/workflows/cmake.yml
[issues-shield]: https://img.shields.io/github/issues/kiddersmxj/stdstreams.svg?style=for-the-badge
[issues-url]: https://github.com/kiddersmxj/stdstreams/issues
[license-shield]: https://img.shields.io/github/license/kiddersmxj/stdstreams.svg?style=for-the-badge
[license-url]: https://github.com/kiddersmxj/stdstreams/blob/master/LICENSE.txt
[product-screenshot]: .images/stdstreams-stdout-mix-0.0.1.png
[stdstreams-mcu-stdout]: .images/stdstreams-mcu-stdout-0.0.1.png
[FTXUI]: https://img.shields.io/badge/FTXUI-563D7C?style=for-the-badge&logo=FTXUI&logoColor=purple
[FTXUI-url]: https://github.com/ArthurSonzogni/FTXUI
[CPP]: https://img.shields.io/badge/CPP-0769AD?style=for-the-badge&logo=cpplogoColor=blue
[CPP-url]: https://cplusplus.com/
