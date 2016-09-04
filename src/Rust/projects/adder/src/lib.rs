//! The `adder` crate provides functions that add numbers to other numbers.
//!
//! # Examples
//!
//! ```
//! assert_eq!(4, adder::add_two(2));
//! ```

/// This function adds two to its argument.
///
/// # Examples
///
/// ```
/// use adder::add_two;
///
/// assert_eq!(4, add_two(2));
/// ```

#[test]
#[should_panic]
fn it_works() {
    assert!(false);
    assert_eq!("Hello", "world");
}

#[test]
#[should_panic(expected = "assertion failed")]
fn it_works_2() {
    assert_eq!("Hello", "world");
}

pub fn add_two(a: i32) -> i32 {
    a + 2
}

#[test]
fn it_works_3() {
    assert_eq!(4, add_two(2));
}

#[cfg(test)]
mod tests {
    use super::add_two;
    //use super::*;

    #[test]
    fn it_works() {
        assert_eq!(4, add_two(2));
    }
}
