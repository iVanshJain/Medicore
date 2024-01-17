-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Nov 23, 2021 at 02:40 PM
-- Server version: 10.4.20-MariaDB
-- PHP Version: 8.0.8

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `medicore`
--

-- --------------------------------------------------------

--
-- Table structure for table `logindetails`
--

CREATE TABLE `logindetails` (
  `id` int(11) NOT NULL,
  `fname` varchar(250) NOT NULL,
  `lname` varchar(250) NOT NULL,
  `email_id` varchar(250) NOT NULL,
  `pass` varchar(250) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `logindetails`
--

INSERT INTO `logindetails` (`id`, `fname`, `lname`, `email_id`, `pass`) VALUES
(5, 'Vidit', 'Talati', 'vidit@gmail.com', 'vidit'),
(6, 'Alimurtuza', 'Patrawala', 'alimurtuza@gmail.com', 'alimurtuza');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `logindetails`
--
ALTER TABLE `logindetails`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `logindetails`
--
ALTER TABLE `logindetails`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
